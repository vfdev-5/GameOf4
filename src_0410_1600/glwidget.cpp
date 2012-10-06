#include "glwidget.h"

GLWidget::GLWidget(GameType type, QSize fieldSize, QWidget *parent) :
    QGLWidget(parent),
    _type(type)
{


    int fszX =fieldSize.width();
    int fszY =fieldSize.height();


    resize(600,600);
    setMinimumSize(600,600);
    setMaximumSize(600,600);

    makeCurrent();
    _painter = new QPainter();

    int fct = max(fszX, fszY);
    int sz = min(width()/(fct+2), height()/(fct+2));
    _scene = new Scene(_painter, QSize(width(), height()), QPoint(sz,sz), sz, fszX, fszY);
    _figures = new PlayersFigures(_painter, _scene);
    _gameRules = new GameRules(fszX, fszY, _figures);

    connect(&_timer,SIGNAL(timeout()), this ,SLOT(timeOutSlot()));

    setAutoFillBackground(true);

}


GLWidget::~GLWidget(){

    if (_painter != NULL){
        delete _painter;
        _painter = NULL;
    }

    if (_scene != NULL){
        delete _scene;
        _scene = NULL;
    }

}


void GLWidget::timeOutSlot()
{
    update();
}


void GLWidget::initializeGL()
{
    _scene->initialize();
    _gameRules->initialize();


    _gameRules->displayGrid();

    _timer.start(100);

}



// ------------------ EVENTS ----------------------------

void GLWidget::closeEvent(QCloseEvent *e)
{
    emit sendClosed();
    e->accept();
}




void GLWidget::paintEvent(QPaintEvent *e)
{
    _painter->begin(this);

    _scene->draw();
    _figures->draw();

    drawMenuButton();

    _painter->end();

}


void GLWidget::drawMenuButton()
{


}


void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    cerr << "GLWidget::mouseDoubleClickEvent(QMouseEvent *event)" << endl;
    if (event->buttons() & Qt::LeftButton){
        // retrieve mouse coordinates
        QPoint gridPos = _figures->convertPointToGridPos(event->pos());
        if (gridPos.x() != -1){

          if (_gameRules->addFigure(_scene->getGameStatus(), gridPos)){
               cerr << "total number of figures: "<< _figures->getTotalNumberOfFigures() << endl;
               if (!_gameRules->gameIsFinished(/*(_scene->getGameStatus()+1)%2)*/))
                    _scene->nextTurn();
               else{
                    _scene->setGameStatus(2);
                    _scene->setWinner(_figures->getWinner());
               }

           }
        }else if (_scene->getSkipButtonRect().contains(event->pos()) && _scene->getGameStatus() < 2){

            cerr << "Skip turn button is pressed" << endl;
            _scene->setSkipButtonPushedStatus(true);
            _scene->nextTurn();

        }else if (_scene->getMenuButtonRect().contains(event->pos())){

            cerr << "menu turn button is pressed" << endl;
            _scene->setMenuButtonPushedStatus(true);

        }
    }


}




