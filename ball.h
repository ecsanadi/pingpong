#ifndef BALL_H
#define BALL_H
#include "line.h"
#include <QSize>

class Ball
{
public:
    Ball();


    void init(QSize iSize, int iBallSize);

    void setBallPosition(int iX, int iY);
    void updateBallPosition(Line iLeftRack, Line iRightRack); //TODO: moving may can be executed from gameboard by adding direction parameters here
    void setBallXDirection(int iXDirection);
    void setBallYDirection(int iYDirection);
    int getBallXDirection();
    int getBallYDirection();
    int getBallX();
    int getBallY();

private:
    int mGameBoardHeight;
    int mGameBoardWidth;
    int mXDirection;
    int mYDirection;
    int mX;
    int mY;
    int mBallSize;



};

#endif // BALL_H
