#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "gameset.h"

class GameRules;

class ComputerPlayer
{
    GameRules * _gameRules;
    typedef QVector< QVector<double> > Matrix;
    Matrix _probaGrid; // probability grid of the turn

    int _type; // for which color (red = 0, blue = 1) computer is playing



public:
    ComputerPlayer(GameRules * gameRules, int type);
    QPoint suggest();

    void reset();

    void displayProbaGrid();

protected:

    void updateProbaGrid();
    int computeDistanceFromPointToNN(int x, int y, int type);


};

#endif // COMPUTERPLAYER_H
