#ifndef GAMESET_H
#define GAMESET_H

#include <QPainter>
#include <QHash>
#include <QVector>

#include <iostream>
using namespace std;


// ------------------- Scene ------------------------------------
class Scene
{
    QPainter * _painter;
    QSize _size;  // size of the Widget

    QBrush _backgroundBrush;
    QBrush _cellBrush;
    QPen _cellPen;

    QRect _cell;
    QPoint _gridStartTL; // Top-left corner
    int _cellSize;
    int _fieldSizeX;
    int _fieldSizeY;

    // buttons:
    QRect _skipButtonRect;
    QRect _menuButtonRect;
    bool _skipButtonPushed;
    bool _menuButtonPushed;
    QColor _skipButtonColor, _skipButtonColorPushed;
    QColor _menuButtonColor, _menuButtonColorPushed;


    // for text font:
    QFont _defaultFont;


    int _gameStatus; // 0 - red's turn, 1 - blue's turn, 2 - end
    int _winner; // 0 - red, 1 - blue, 2 - friendship




public:
    Scene(QPainter * painter, QSize size, QPoint gstart, int cellSize, int fszX, int fszY) :
        _painter(painter),
        _size(size),
        _gridStartTL(gstart),
        _cellSize(cellSize),
        _fieldSizeX(fszX),
        _fieldSizeY(fszY)
    {}

    void initialize();
    void draw();


    inline QPoint getGridStartTL() {return _gridStartTL;}
    inline int getCellSize() {return _cellSize;}
    inline int getFieldSizeX() {return _fieldSizeX;}
    inline int getFieldSizeY() {return _fieldSizeY;}

    inline int getGameStatus() {return _gameStatus;}
    inline void setGameStatus(int status) {_gameStatus = status;}
    inline void nextTurn() {_gameStatus = (_gameStatus+1) % 2;}
    inline void setWinner(int w) {_winner = w;}

    inline QRect getSkipButtonRect() {return _skipButtonRect;}
    inline void setSkipButtonPushedStatus(bool status) {_skipButtonPushed = status;}
    inline QRect getMenuButtonRect() {return _menuButtonRect;}
    inline void setMenuButtonPushedStatus(bool status) {_menuButtonPushed = status;}

private:

};


// ----------------------------- Figures ---------------------------------
class Figure
{
protected:
    QPainter * _painter;
    QPoint _position;

public:
    Figure(QPainter * painter, QPoint position) :
        _painter(painter), _position(position)
    {}
    virtual ~Figure(){}
    virtual void draw() = 0;
};

class SimpleFigure : public Figure
{
    int _cellSize;
    int _playerType; // 0 - red, 1 - blue

    // items:
    QBrush _itemBrush;
    QPen _itemPen;

public:
    SimpleFigure(int playerType,int cs, QPainter * painter, QPoint position) :
        Figure(painter, position), _cellSize(cs), _playerType(playerType)
    {
        // set players' items properties:
        float rad = _cellSize/2 - _cellSize/10;
        QRadialGradient radialGradient(QPoint(position + QPoint(-rad/5,-rad/7)), rad);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(1.0, Qt::black);

        if (_playerType==0){ // red
            radialGradient.setColorAt(0.3, Qt::red);
        }else{ // blue
            radialGradient.setColorAt(0.3, Qt::blue);
        }
        _itemBrush = QBrush(radialGradient);
        _itemPen = QPen(Qt::black);
    }
    ~SimpleFigure(){}
    virtual void draw(){
        _painter->setPen(_itemPen);
        _painter->setBrush(_itemBrush);
        int rad = _cellSize/2 - _cellSize/10;
        _painter->drawEllipse(_position, rad, rad);
    }

};

// -------------------------------- PlayerFigures -------------------------------
class GameRules;

class PlayersFigures
{
    QPainter * _painter;
    QPoint _gridStartTL;
    int _cellSize;
    int _fieldSizeX;
    int _fieldSizeY;
    QRect _playBoard;


    QHash<int, Figure *> _player1;  // set of figures of the 1st player
    QHash<int, Figure *> _player2;  // set of figures of the 2nd player


public:
    enum PlayerType {RED, BLUE};
    PlayersFigures(QPainter * painter, Scene * scene);
    ~PlayersFigures();



    void draw();


    QPoint convertGridPosToPoint(int x, int y); // convert grid position to QPoint
    QPoint convertGridPosToPoint(QPoint xy); // convert grid position to QPoint

    QPoint convertPointToGridPos(QPoint p); // convert QPoint mouse position to grid position
    int uniqueIndex(int x, int y){ return x + y*_fieldSizeX;}

    inline int getTotalNumberOfFigures(){return _player1.size() + _player2.size();}
    inline int getWinner() {
        if (_player1.size() > _player2.size())
            return 0; // red
        else if (_player1.size() == _player2.size())
            return 2; // friendship
        else
            return 1; // blue
    }
    inline int getSurfaceOfPlayboard(){return _fieldSizeX * _fieldSizeY;}

private:
    void initialize();
    void addFigure(PlayerType type, int x, int y);
    void addFigure(int type, QPoint p); // p is the point on the grid
    void deleteFigure(int type, QPoint p);

    friend class GameRules;

};




// --------------------------------- Game rules ---------------------------
// a method from the class is called :
// input : grid coordinates
//

class GameRules
{
    typedef QVector< QVector<int> > Matrix;
    Matrix _grid; // -1 - cell is free, 0 - red, 1 - blue
    int _fieldSizeX;
    int _fieldSizeY;
    PlayersFigures * _figures;


    QPoint justDeletedFigure; // for the special rule that if e.g. blue's figure has been beaten with a red one, but it can be beaten on the next turn with the blue figure -> dead-lock. The rule is to forbidden this move

public:
    GameRules(int fx, int fy, PlayersFigures *);
    ~GameRules();


    void initialize();
    bool addFigure(int type, QPoint p);  // p is the point on the grid

    bool gameIsFinished();

    // for debugs:
    void displayGrid();

private:
    inline bool isInside(int x, int y) {return (x>=0 && x < _fieldSizeX && y >= 0 && y < _fieldSizeY) ? true : false;}
    inline bool isInside(QPoint p) {return isInside(p.x(), p.y());}
    // rules:
    inline bool isFree(int x, int y) {return (_grid[x][y]==-1) ? true : false;}
    inline bool isFree(QPoint p) {return isFree(p.x(),p.y());}

    bool canBeatOpponentFigure(int type, int x, int y);
    QVector<QPoint> checkForFigureToBeTaken(int type);

};





#endif // GAMESET_H
