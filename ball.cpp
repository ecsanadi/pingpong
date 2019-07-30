#include "ball.h"

Ball::Ball()
{

}

void Ball::init(QSize iSize, int iBallSize)
{
    //TODO: set size of gameboard to handle ball moving
    mGameBoardHeight = iSize.height();
    mGameBoardWidth = iSize.width();
    mBallSize = iBallSize;
    mXDirection = 1;
    mYDirection = -1;

}

void Ball::setBallPosition(int x, int y)
{
    mX = x;
    mY = y;
}

void Ball::updateBallPosition()
{
    int wXCheckpoint = mX + mXDirection + (mBallSize / 2);
    int wYCheckpoint = mY + mYDirection + (mBallSize / 2);
    int wSpeed = 4;

    if(wXCheckpoint < 0 || wXCheckpoint > mGameBoardWidth)
    {
        mXDirection *= -1;
    }
    if(wYCheckpoint < 0 || wYCheckpoint > mGameBoardHeight)
    {
        mYDirection *= -1;
    }
    mX += (mXDirection * wSpeed);
    mY += (mYDirection * wSpeed);
}

void Ball::setBallXDirection(int iXDirection)
{
    mXDirection = iXDirection;
}

void Ball::setBallYDirection(int iYDirection)
{
    mYDirection = iYDirection;
}

int Ball::getBallXDirection()
{
    return mXDirection;
}

int Ball::getBallYDirection()
{
    return mYDirection;
}

int Ball::getBallX()
{
    return mX;
}

int Ball::getBallY()
{
    return mY;
}
