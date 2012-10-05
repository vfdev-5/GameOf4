#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include "gameset.h"

#include <iostream>
using namespace std;



// -------------------------- GamePlay widget -------------------------------
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    enum GameType {HeadToHead, HumanVsMachine};
    explicit GLWidget(GameType type=HeadToHead, QSize fieldSize=QSize(4,4), QWidget *parent = 0);
    ~GLWidget();

protected:
    void closeEvent(QCloseEvent *);

    void mouseDoubleClickEvent(QMouseEvent * event);

    void initializeGL();
    void paintEvent(QPaintEvent *);

    void drawMenuButton();

signals:
    void sendClosed();
    
protected slots:
    void timeOutSlot();


private :
    GameType _type;
    QPainter * _painter;
    Scene * _scene;
    PlayersFigures * _figures;
    GameRules * _gameRules;
    QTimer _timer;


};







#endif // GLWIDGET_H
