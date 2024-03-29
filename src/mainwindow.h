#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "glwidget.h"
#include "graphicstools.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //GLWidget * _gameplay;
    GraphicsScene::GameType _type;

    GraphicsScene * _gamePlayScene;
    GraphicsView * _gamePlayView;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_startButton_clicked();

    void onGamePlayExit();

    void on_comboBox_currentIndexChanged(int index);

    void on_swapB_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
