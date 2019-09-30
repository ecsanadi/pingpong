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
    void updateBallPosition(Line iLeftRack, Line iRightRack, int &iLScore, int &iRScore);
    void setBallXDirection(int iXDirection);
    void setBallYDirection(int iYDirection);
    int getBallXDirection();
    int getBallYDirection();
    int getBallX();
    int getBallY();
    bool getIsBallOut(){return mIsBallOut;}

private:
    int mGameBoardHeight;
    int mGameBoardWidth;
    int mXDirection;
    int mYDirection;
    int mX;
    int mY;
    int mBallSize;
    bool mIsBallOut;



};

#endif // BALL_H
