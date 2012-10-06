#include "dialogmenu.h"
#include "ui_dialogmenu.h"

DialogMenu::DialogMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMenu)
{
    ui->setupUi(this);

    initialize();
}

DialogMenu::~DialogMenu()
{
    delete ui;
}

void DialogMenu::initialize()
{
    ui->undoLastMoveB->setEnabled(false);
    ui->resetGameB->setEnabled(false);
    setNumberOfRedFigures(1);
    setNumberOfBlueFigures(1);
}


void DialogMenu::on_menuCloseB_clicked()
{
    emit sendCloseMenu();
}

void DialogMenu::on_undoLastMoveB_clicked()
{
    emit sendUndoLastMove();
}

void DialogMenu::on_numOfRedFigLE_textChanged(const QString &arg1)
{
    int val = arg1.toInt();
    int val2 = ui->numOfBlueFigLE->text().toInt();

    if (val > 1 && !ui->undoLastMoveB->isEnabled()){
        ui->undoLastMoveB->setEnabled(true);
        ui->resetGameB->setEnabled(true);
    }

    if (val == 1 && val2 == 1){
        ui->undoLastMoveB->setEnabled(false);
        ui->resetGameB->setEnabled(false);
    }
}

void DialogMenu::on_numOfBlueFigLE_textChanged(const QString &arg1)
{
    int val = arg1.toInt();
    int val2 = ui->numOfRedFigLE->text().toInt();

    if (val > 1 && !ui->undoLastMoveB->isEnabled()){
        ui->undoLastMoveB->setEnabled(true);
        ui->resetGameB->setEnabled(true);
    }

    if (val == 1 && val2 == 1){
        ui->undoLastMoveB->setEnabled(false);
        ui->resetGameB->setEnabled(false);
    }
}


void DialogMenu::setNumberOfRedFigures(int n)
{
    ui->numOfRedFigLE->setText(QString("%1").arg(n));
}

void DialogMenu::setNumberOfBlueFigures(int n)
{
    ui->numOfBlueFigLE->setText(QString("%1").arg(n));
}

void DialogMenu::addToRedFigures(int delta)
{
    int val = ui->numOfRedFigLE->text().toInt();
    val += delta;
    ui->numOfRedFigLE->setText(QString("%1").arg(val));

}

void DialogMenu::addToBlueFigures(int delta)
{
    int val = ui->numOfBlueFigLE->text().toInt();
    val += delta;
    ui->numOfBlueFigLE->setText(QString("%1").arg(val));
}

void DialogMenu::on_resetGameB_clicked()
{
    initialize();
    emit  sendResetGame();
}
