#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (ui->comboBox->currentIndex()==0){
        _type = GLWidget::HeadToHead;
    }else if (ui->comboBox->currentIndex()==1){
        _type = GLWidget::HumanVsMachine;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

    int fszX = ui->fieldSizeX->value();
    int fszY = ui->fieldSizeY->value();

    _gameplay = new GLWidget(_type, QSize(fszX, fszY));

    // on _gameplay exit:
    connect(_gameplay,SIGNAL(sendClosed()),SLOT(onGamePlayExit()),Qt::QueuedConnection);

    _gameplay->show();

    this->hide();
}


void MainWindow::onGamePlayExit()
{
    if (_gameplay!=NULL){
        delete _gameplay;
        _gameplay = NULL;
    }
    this->show();
}
