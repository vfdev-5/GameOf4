#ifndef DIALOGMENU_H
#define DIALOGMENU_H

#include <QDialog>



namespace Ui {
class DialogMenu;
}

class DialogMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMenu(QWidget *parent = 0);
    ~DialogMenu();

    void initialize();

public slots:
    void setNumberOfRedFigures(int n);
    void setNumberOfBlueFigures(int n);
    void addToRedFigures(int delta);
    void addToBlueFigures(int delta);
    
signals:
    void sendCloseMenu();
    void sendUndoLastMove();
    void sendResetGame();

private slots:
    void on_menuCloseB_clicked();
    void on_undoLastMoveB_clicked();
    void on_resetGameB_clicked();

    void on_numOfRedFigLE_textChanged(const QString &arg1);
    void on_numOfBlueFigLE_textChanged(const QString &arg1);



private:
    Ui::DialogMenu *ui;
};

#endif // DIALOGMENU_H
