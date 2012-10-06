#ifndef GRAPHICSTOOLS_H
#define GRAPHICSTOOLS_H

// GraphicsTools : GraphicsView and GraphicsScene - two implementation of QGraphicsView and QGraphicsScene
// similar to qt-labs\modelviewer example

// GraphicsView will be shown as gamePlay in the MainWindow
// GraphicsScene will be used to contain GLWidget and GameMenu

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGLWidget>
#include <QtOpenGL>
#include <QMessageBox>


#include "gameset.h"
#include "dialogmenu.h"

#include "computerplayer.h"

#include <iostream>
using namespace std;




// ----------------------------------------- class GraphicsView --------------------------------------------------
class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene * scene):
        QGraphicsView(scene)
    {
        setWindowTitle(tr("Game Of 4"));
        resize(scene->width(), scene->height());
        cerr << "GraphicsView : scene size : " << this->size().width() << ", " << this->size().height() << endl;
    }

protected:

    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }

    void closeEvent(QCloseEvent * e){
        // int ret = QMessageBox(QMessageBox::Warning, )
        emit sendClosed();
        e->accept();
    }


signals:
    void sendClosed();


};





// -------------------------------------------  class GraphicsScene  -------------------------------------------
class GraphicsScene : public QGraphicsScene
{

    Q_OBJECT

public:
    enum GameType {HeadToHead, HumanVsMachine, MachineVsHuman, MachineVsMachine};
    GraphicsScene(GameType type, QSize fieldSize, QRect sceneSize);

    ~GraphicsScene();

    void drawBackground(QPainter *painter, const QRectF &rect);


protected:
      void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
      void moveOnPosition(QPoint p);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);

signals:
      void sendAddToRedFigures(int);
      void sendAddToBlueFigures(int);

protected slots:
      void nextTurn();
      void openMenu();
      void closeMenu();
      void undoLastMove();
      void resetGame();

private:
    GameType _type;
    QPainter * _painter;
    Scene * _scene;
    PlayersFigures * _figures;
    GameRules * _gameRules;

    ComputerPlayer * _computerMind;
    ComputerPlayer * _computerMind2; // 2nd machinePlayer
    int _computerType;

    // buttons:
    QWidget * _skipTurnButton;
    QWidget * _menuOpenButton;
    QWidget * _menuCloseButton;
    DialogMenu * _dialogMenu;

    // timer for update scene and figures
    QTimer * _timer;

};









#endif // GRAPHICSTOOLS_H
