#include "gameset.h"

//======================== SCENE ==================================
void Scene::initialize()
{
    //QColor bgColor(252,247,180);
    //_backgroundBrush = QBrush(bgColor);
    _backgroundBrush = QBrush(QImage("data/bg.jpg"));

    _cellBrush = QBrush(QColor(255,255,255,120));
    _cellPen = QPen(Qt::black);
    _cell = QRect(QPoint(0,0), QSize(_cellSize,_cellSize));

    _gameStatus = 0;

    _skipButtonRect = QRect((_fieldSizeX+1.1)*_cellSize, (_fieldSizeY+1)*_cellSize + _cellSize/3,_cellSize*0.7,_cellSize*0.5 );
    _skipButtonPushed = false;
    _skipButtonColor = QColor(200,200,255,120);
    _skipButtonColorPushed = QColor(220,220,255,150);

    _menuButtonRect = QRect((0.1)*_cellSize, _cellSize/3,_cellSize*0.7,_cellSize*0.5 );
    _menuButtonPushed = false;
    _menuButtonColor = QColor(200,200,255,120);
    _menuButtonColorPushed = QColor(220,220,255,150);

    _defaultFont = QFont("Helvetica [Cronyx]",20, QFont::Bold);
}



void Scene::draw()
{
    // draw backgroung rectangle:
    _painter->setBrush(_backgroundBrush);
    _painter->drawRect(QRect(0, 0, _size.width(), _size.height()));


    // draw cells of the battlefield:
    _painter->setPen(_cellPen);
    _painter->setBrush(_cellBrush);
    for (int i=0;i<_fieldSizeX;i++){
        for (int j=0;j<_fieldSizeY;j++){
            _painter->save();
            _painter->translate(_gridStartTL + QPoint(_cellSize*i,_cellSize*j));
            _painter->drawRoundRect(_cell);
            _painter->restore();
        }
    }

    // draw 'menu' button and 'skip turn' button
    if (_skipButtonPushed){
        _painter->setBrush(_skipButtonColorPushed);
        _skipButtonPushed = false;
    }else
        _painter->setBrush(_skipButtonColor);

    _painter->drawRoundedRect(_skipButtonRect,20.,15.);
    _painter->setPen(Qt::black);
    _painter->drawText(_skipButtonRect, Qt::AlignCenter, "Skip turn");



    if (_menuButtonPushed){
        _painter->setBrush(_menuButtonColorPushed);
        _menuButtonPushed = false;
    }else{
        _painter->setBrush(_menuButtonColor);
    }
    _painter->drawRoundedRect(_menuButtonRect,20.,15.);
    _painter->setPen(Qt::white);
    _painter->drawText(_menuButtonRect, Qt::AlignCenter, "Menu");



    // draw text and who's turn:
    QString text;
    if (_gameStatus == 0)
        text = "Red's turn";
    else if (_gameStatus == 1)
        text = "Blue's turn";
    else if (_gameStatus == 2){
        text = "Game is finished: ";
        if (_winner == 0)
            text += "aka no kachi";
        else if (_winner == 1)
            text += "ao no kachi";
        else
            text += "torimasen";
    }

    _painter->setFont(_defaultFont);
    _painter->setPen(Qt::black);
    _painter->drawText(0,0,_size.width()-1,_cellSize, Qt::AlignCenter, text);
    //_painter->drawText(QPointF(_size.width()/3, _cellSize/2), text);
    _painter->setPen(Qt::white);
    _painter->drawText(1,1,_size.width(),_cellSize+1, Qt::AlignCenter, text);
    //_painter->drawText(QPointF(_size.width()/3 + 1, _cellSize/2 + 1), text);


}




// ================================== PlayersFigures ========================================
PlayersFigures::PlayersFigures(QPainter *painter, Scene *scene):
    _painter(painter)
{
    _gridStartTL = scene->getGridStartTL();
    _cellSize = scene->getCellSize();
    _fieldSizeX = scene->getFieldSizeX();
    _fieldSizeY = scene->getFieldSizeY();

    QPoint _gridFinishBR = _gridStartTL + QPoint(_cellSize*_fieldSizeX, _cellSize*_fieldSizeY);
    _playBoard = QRect(_gridStartTL, _gridFinishBR);

}

PlayersFigures::~PlayersFigures()
{
    int s1 = _player1.size();
    while (s1 > 0){
        delete _player1[s1-1];
        s1--;
    }

    int s2 = _player2.size();
    while (s2 > 0){
        delete _player2[s2-1];
        s2--;
    }


}


void PlayersFigures::initialize()
{


    // initial disposition:
    // (fszX-1,0) coordinate:
    addFigure(RED, _fieldSizeX-1, 0);

    // (0, fszY-1) coordinate:
    addFigure(BLUE, 0, _fieldSizeY-1);




}


QPoint PlayersFigures::convertGridPosToPoint(int x, int y)
{
    return QPoint(_gridStartTL + QPoint(x*_cellSize + _cellSize/2, y*_cellSize + _cellSize/2));
}

QPoint PlayersFigures::convertGridPosToPoint(QPoint xy)
{
    return QPoint(_gridStartTL + QPoint(xy.x()*_cellSize + _cellSize/2, xy.y()*_cellSize + _cellSize/2));
}



QPoint PlayersFigures::convertPointToGridPos(QPoint p)
{
    cerr << "PlayersFigures::convertPointToGridPos(QPoint p)" << endl;
    if (_playBoard.contains(p, true)){

        cerr << "p: " << p.x() << ", " << p.y() << endl;
        int x = (int)((p.x() - _gridStartTL.x())/_cellSize);
        int y = (int)((p.y() - _gridStartTL.y())/_cellSize);
        cerr << "x,y: " << x << ", " << y << endl;
        return QPoint(x,y);

    }else{
        //cerr << "position is outside" << endl;
        return QPoint(-1,-1);
    }


}


void PlayersFigures::addFigure(PlayerType type, int x, int y)
{

    if (type==RED){
        Figure * pos1 = new SimpleFigure(0, _cellSize, _painter, convertGridPosToPoint(x,y));
        int index = uniqueIndex(x,y);
        _player1.insert(index, pos1);
    }else if (type ==BLUE){
        Figure * pos1 = new SimpleFigure(1, _cellSize, _painter, convertGridPosToPoint(x,y));
        int index = uniqueIndex(x,y);
        _player2.insert(index, pos1);
    }
}

void PlayersFigures::addFigure(int type, QPoint p)
{
    if (type==0){ // red
        Figure * pos1 = new SimpleFigure(0, _cellSize, _painter, convertGridPosToPoint(p));
        int index = uniqueIndex(p.x(),p.y());
        _player1.insert(index, pos1);
    }else if (type ==1){ // blue
        Figure * pos1 = new SimpleFigure(1, _cellSize, _painter, convertGridPosToPoint(p));
        int index = uniqueIndex(p.x(),p.y());
        _player2.insert(index, pos1);
    }
}


void PlayersFigures::deleteFigure(int type, QPoint p)
{
    if (type==0){ // red
        int index = uniqueIndex(p.x(),p.y());
        _player1.remove(index);
    }else if (type ==1){ // blue
        int index = uniqueIndex(p.x(),p.y());
        _player2.remove(index);
    }
}


void PlayersFigures::draw()
{


    // draw warriors:
    // _player1 :
    QHash<int, Figure *>::iterator iter1 = _player1.begin();
    for (; iter1!=_player1.end();iter1++){
        (*iter1)->draw();
    }

    // _player2 :
    QHash<int, Figure *>::iterator iter2 = _player2.begin();
    for (; iter2!=_player2.end();iter2++){
        (*iter2)->draw();

    }


}





// ================================= GAME RULES =================================================
GameRules::GameRules(int fx, int fy, PlayersFigures *figures):
    _fieldSizeX(fx), _fieldSizeY(fy), _figures(figures)
{
    _grid.resize(_fieldSizeX);
    // initialize the grid:
    for (int i=0;i<_fieldSizeX;i++){
        _grid[i].resize(_fieldSizeY);
        for (int j=0;j<_fieldSizeY;j++){
            _grid[i][j] = -1;
        }
    }

    //
    justDeletedFigure = QPoint(-1,-1);

}


GameRules::~GameRules()
{
}


void GameRules::initialize()
{
    // set initial warriors:
    _grid[_fieldSizeX-1][0] = 0; // red
    _grid[0][_fieldSizeY-1] = 1; // blue
    _figures->initialize();
}


bool GameRules::addFigure(int type, QPoint p)
{

    if (isInside(p)){
        if (isFree(p)){
            _grid[p.x()][p.y()] = type;
            _figures->addFigure(type, p);
            justDeletedFigure = QPoint(-1,-1);
            displayGrid();
            return true;
        }else{
            cerr << "grid is occupied" << endl;
            // type is the color of figure user want to place
            if (canBeatOpponentFigure(type, p.x(),p.y()) && p != justDeletedFigure){
                _grid[p.x()][p.y()] = type;
                _figures->deleteFigure((type+1)%2,p);
                justDeletedFigure = p;
                _figures->addFigure(type, p);
                displayGrid();
                return true;
            }

        }
    }

    return false;
}




// ----- rules:
/** canBeatOpponentFigure(int x, int y) rule. True : if there are two figures of the same color at the neighbourhood forming a cross.
    example,    | |x| |
                |x|O|x|
                | |x| |
    'type' here is the color of neighbours (x).
*/
bool GameRules::canBeatOpponentFigure(int type, int x, int y)
{
    if (_grid[x][y] == type) // empty cells are already neglected
        return false;

    // _grid[x][y] = (type + 1) % 2 // opposite type
    QPoint n[4];
    n[0] = QPoint(x-1,y);
    n[1] = QPoint(x+1,y);
    n[2] = QPoint(x,y-1);
    n[3] = QPoint(x,y+1);
    int nn=0;
    for (int i=0;i<4;i++){
        if (isInside(n[i])){
            if (_grid[n[i].x()][n[i].y()] == type)
                nn++;
        }
    }

    if (nn >=2)
        return true;
    else
        return false;
}

//! Checks for the given type (e.g. red) if some other figures (resp. blue) can be taken
QVector<QPoint> GameRules::checkForFigureToBeTaken(int type)
{
    cerr << "QVector<QPoint> GameRules::checkForFigureToBeTaken(int type): type = " << type << endl;
    QVector<QPoint> result;
    for (int i=0;i<_fieldSizeX;i++){
        for (int j=0;j<_fieldSizeY;j++){

            if (canBeatOpponentFigure(type, i, j) && QPoint(i,j) != justDeletedFigure){
                result.push_back(QPoint(i,j));
            }
        }
    }
    cerr << "   result.size() = " << result.size() << endl;
    return result;
}




bool GameRules::gameIsFinished()
{
   if (_figures->getTotalNumberOfFigures() < _figures->getSurfaceOfPlayboard())
       return false;
   else{
       // check if no figures can be beaten :
       if (checkForFigureToBeTaken(0).size() == 0 && checkForFigureToBeTaken(1).size() == 0){
           return true;
       }else{
           return false;
       }
   }


}





// ----- for debug:
void GameRules::displayGrid()
{
    cerr << "GameRules: grid size : " << _fieldSizeX << ", " << _fieldSizeY << endl;
    cerr << "-----" << endl;
    for (int i=0;i<_fieldSizeY;i++){
        cerr << "[ ";
        for (int j=0;j<_fieldSizeX;j++){
            cerr << _grid[j][i] << ", ";
        }
        cerr << "]" << endl;
    }
    cerr << "-----" << endl;


}

