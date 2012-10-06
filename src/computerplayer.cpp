#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(GameRules * gameRules, int type):
    _gameRules(gameRules), _type(type)
{
    reset();

}



void ComputerPlayer::reset()
{

    _probaGrid.clear();

    _probaGrid.resize(_gameRules->_fieldSizeX);
    // initialize the grid:
    for (int i=0;i<_gameRules->_fieldSizeX;i++){
        _probaGrid[i].resize(_gameRules->_fieldSizeY);
        for (int j=0;j<_gameRules->_fieldSizeY;j++){
            _probaGrid[i][j] = 0;
        }
    }

}


void ComputerPlayer::updateProbaGrid()
{
    int c1 =(int)(_gameRules->_fieldSizeX/2) - 1;
    int c2 =(int)(_gameRules->_fieldSizeX/2);
    int c3 = (int)(_gameRules->_fieldSizeX/2) + 1;

    for (int i=0;i<_gameRules->_fieldSizeX;i++){
        for (int j=0;j<_gameRules->_fieldSizeY;j++){

            // test on the computer color -> can not place figures on already placed figures
            if (_gameRules->_grid[i][j] != -1 ){
                _probaGrid[i][j] = 0;
                continue;
            }

            // figures on the principal diagonal near the center is good += 0.2
            if (i==j && (i==c1 || i==c2 || i == c3)){
                _probaGrid[i][j] += 0.2;
            }

            // figures near the others of the same camp is good += 0.3*(1/distance to the nearest)
             _probaGrid[i][j] +=  0.25/computeDistanceFromPointToNN(i,j,_type);

        }
    }

    // check if some opponent figures can be taken: += 0.5
    QVector<QPoint> pts = _gameRules->checkForFigureToBeTaken(_type);
    QVector<QPoint>::iterator iter = pts.begin();
    for (;iter!=pts.end();++iter){
        int x = (*iter).x();
        int y = (*iter).y();
        _probaGrid[x][y] += 0.5;
    }




}


int ComputerPlayer::computeDistanceFromPointToNN(int x, int y, int type)
{
    //cerr << "computeDistanceFromPointToNN: x, y = " << x << ", " << y << endl;
    int minDist = _gameRules->_fieldSizeX + _gameRules->_fieldSizeY;

    for (int i=0;i<_gameRules->_fieldSizeX;i++){
        for (int j=0;j<_gameRules->_fieldSizeY;j++){
            if (_gameRules->_grid[i][j] != type)
                continue;

            int dist = abs(x - i) + abs(y - j);
            if (dist < minDist){
                minDist = dist;
            }
        }
    }

    //cerr << "minDist : " << minDist << endl;
    return minDist;
}



QPoint ComputerPlayer::suggest()
{
    int x=0;
    int y=0;
    reset();

    updateProbaGrid();

    displayProbaGrid();

    // find 1st maximum proba QPoint:
    double maxProba=0;
    for (int i=0;i<_gameRules->_fieldSizeX;i++){
        for (int j=0;j<_gameRules->_fieldSizeY;j++){
            if (_probaGrid[i][j] > maxProba){
                 maxProba = _probaGrid[i][j];
                 x = i;
                 y = j;
            }
        }
    }

    if (maxProba == 0){
        return QPoint(-1,-1); // skip turn
    }


    return QPoint(x,y);
}


void ComputerPlayer::displayProbaGrid()
{
    cerr << "Computer: probaGrid size : " << _gameRules->_fieldSizeX << ", " << _gameRules->_fieldSizeY << endl;
    cerr << "-----" << endl;
    for (int i=0;i<_gameRules->_fieldSizeY;i++){
        cerr << "[ ";
        for (int j=0;j<_gameRules->_fieldSizeX;j++){
            cerr << _probaGrid[j][i] << ", ";
        }
        cerr << "]" << endl;
    }
    cerr << "-----" << endl;


}
