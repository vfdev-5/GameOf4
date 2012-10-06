#include "graphicstools.h"

// --------------------- Graphics Scene -------------------------------------------------

GraphicsScene::GraphicsScene(GameType type, QSize fieldSize, QRect sceneSize):
    _type(type), QGraphicsScene(sceneSize)
{

    int fszX =fieldSize.width();
    int fszY =fieldSize.height();

    cerr << "GraphicsScene : scene size : " << this->width() << ", " << this->height() << endl;


    int fct = max(fszX, fszY);
    int sz = min(width()/(fct+3), height()/(fct+3));
    _scene = new Scene(QSize(width(), height()), QPoint(sz*1.5,sz*1.5), sz, fszX, fszY);
    _figures = new PlayersFigures(_scene);
    _gameRules = new GameRules(fszX, fszY, _figures);

    _timer = new QTimer(this);
    connect(_timer,SIGNAL(timeout()), this ,SLOT(update()));


    // set "Skip turn" button:
    _skipTurnButton = new QPushButton(tr("Skip turn"));
    _skipTurnButton->resize(80,40);
    connect(_skipTurnButton, SIGNAL(clicked()), SLOT(nextTurn()));
    _skipTurnButton->move(width() - 100, height() - 50);
    _skipTurnButton->setWindowOpacity(0.8);

    // set "Menu" button
    _menuOpenButton = new QPushButton(tr("Menu"));
    _menuOpenButton->resize(80,40);
    connect(_menuOpenButton, SIGNAL(clicked()), SLOT(openMenu()));
    _menuOpenButton->move((0.1)*sz, sz/3);
    _menuOpenButton->setWindowOpacity(0.8);

    // set "Menu" :
    _dialogMenu = new DialogMenu();
    connect(_dialogMenu, SIGNAL(sendCloseMenu()), SLOT(closeMenu()));
    connect(_dialogMenu, SIGNAL(sendUndoLastMove()), SLOT(undoLastMove()));
    connect(_dialogMenu, SIGNAL(sendResetGame()), SLOT(resetGame()));
    connect(this, SIGNAL(sendAddToRedFigures(int)), _dialogMenu, SLOT(addToRedFigures(int)));
    connect(this, SIGNAL(sendAddToBlueFigures(int)), _dialogMenu, SLOT(addToBlueFigures(int)));
    _dialogMenu->move(_menuOpenButton->pos());
    _dialogMenu->setWindowOpacity(0.85);
    _dialogMenu->hide();
    QWidget * _dialogMenuWidget = dynamic_cast<QWidget *>(_dialogMenu);


    // add all widgets in GraphicsScene as
    QWidget *widgets[] = { _skipTurnButton, _menuOpenButton, _dialogMenuWidget };

    for (uint i = 0; i < sizeof(widgets) / sizeof(*widgets); ++i) {
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(0);
        proxy->setWidget(widgets[i]);
        addItem(proxy);
    }


    // setup ComputerPlayer:
    if (_type==HumanVsMachine){
        _computerType = 1;
        _computerMind = new ComputerPlayer(_gameRules, _computerType);
    }else if (_type==MachineVsHuman){
        _computerType = 0;
        _computerMind = new ComputerPlayer(_gameRules, _computerType);
    }else if (_type == MachineVsMachine){
        _computerMind = new ComputerPlayer(_gameRules, 0);
        _computerMind2 = new ComputerPlayer(_gameRules, 1);
    }




    // initialize():
    _scene->initialize();
    _gameRules->displayGrid();
    _timer->start(100);


    // start computerMind:
    if (_type==MachineVsHuman || _type==MachineVsMachine){

        QPoint p = _computerMind->suggest();
        cerr << "suggest: " << p.x() << ", " << p.y() << endl;
        if (p.x() >= 0 && p.y() >= 0){
            moveOnPosition(p);
        }else{
            // skip turn:
            nextTurn();
        }

    }

}





GraphicsScene::~GraphicsScene()
{
    cerr << "GraphicsScene::~GraphicsScene()" << endl;
}




void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{

    _scene->draw(painter);
    _figures->draw(painter);

}



void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    cerr << "GLWidget::mouseDoubleClickEvent(QMouseEvent *event)" << endl;

    QGraphicsScene::mouseDoubleClickEvent(event);
    if (event->isAccepted())
        return;


    cerr << "pos: " << event->scenePos().x() << ", " << event->scenePos().y() << endl;
    if (event->buttons() & Qt::LeftButton){
        // retrieve mouse coordinates
        QPoint gridPos = _figures->convertPointToGridPos(event->scenePos().toPoint());
        if (gridPos.x() != -1){

            moveOnPosition(gridPos);

        } // endif (gridPos.x() != -1){
    }

    event->accept();

}



void GraphicsScene::moveOnPosition(QPoint p)
{
    int playerType = _scene->getGameStatus(); // red or blue
    if (_gameRules->addFigure(playerType, p)){

         _dialogMenu->setNumberOfRedFigures(_figures->getNumberOfRedFigures());
         _dialogMenu->setNumberOfBlueFigures(_figures->getNumberOfBlueFigures());

         cerr << "total number of figures: "<< _figures->getTotalNumberOfFigures() << endl;
         if (!_gameRules->gameIsFinished(/*(_scene->getGameStatus()+1)%2)*/)){

             nextTurn();

         }else{
              _scene->setGameStatus(2);
              _scene->setWinner(_figures->getWinner());
         }
     }// endif if (_gameRules->addFigure(playerType, gridPos))


}


// -------- slots ----------------

void GraphicsScene::nextTurn() {
    if (_scene->getGameStatus() < 2){
        _scene->nextTurn();

        if (_type == MachineVsHuman || _type == HumanVsMachine){
            if (_scene->getGameStatus() == _computerType){
                QPoint p = _computerMind->suggest();
                cerr << "computerMind of type : " << _computerType << " suggest: " << p.x() << ", " << p.y() << endl;
                if (p.x() >= 0 && p.y() >= 0){
                    moveOnPosition(p);
                }else{
                    // skip turn:
                    nextTurn();
                }
            }
        }else if (_type == MachineVsMachine){
            if (_scene->getGameStatus() == _computerType){
                QPoint p = _computerMind->suggest();
                cerr << "suggest: " << p.x() << ", " << p.y() << endl;
                if (p.x() >= 0 && p.y() >= 0){
                    moveOnPosition(p);
                }else{
                    // skip turn:
                    nextTurn();
                }
            }else{
                QPoint p = _computerMind2->suggest();
                cerr << "suggest: " << p.x() << ", " << p.y() << endl;
                if (p.x() >= 0 && p.y() >= 0){
                    moveOnPosition(p);
                }else{
                    // skip turn:
                    nextTurn();
                }
            }

        }

    }
}


void GraphicsScene::openMenu()
{
    _menuOpenButton->setEnabled(false);
    _dialogMenu->show();
}


void GraphicsScene::closeMenu()
{
    _dialogMenu->hide();
    _menuOpenButton->setEnabled(true);
}

void GraphicsScene::undoLastMove()
{
    _gameRules->undoLastMove();
    _dialogMenu->setNumberOfRedFigures(_figures->getNumberOfRedFigures());
    _dialogMenu->setNumberOfBlueFigures(_figures->getNumberOfBlueFigures());
    _scene->nextTurn();
}


void GraphicsScene::resetGame()
{
    _scene->setGameStatus(0);
    _gameRules->reset();



    // start computerMind:
    if (_type==MachineVsHuman || _type==MachineVsMachine){

        QPoint p = _computerMind->suggest();
        cerr << "suggest: " << p.x() << ", " << p.y() << endl;
        if (p.x() >= 0 && p.y() >= 0){
            moveOnPosition(p);
        }else{
            // skip turn:
            nextTurn();
        }

    }

}

