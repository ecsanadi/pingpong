#include "ball.h"

Ball::Ball()
{

}

void Ball::init(QSize iSize, int iBallSize)
{
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

void Ball::updateBallPosition(Line iLeftRack, Line iRightRack)
{    
    int wXCheckpoint = mX + mXDirection + (mBallSize / 2);
    int wYCheckpoint = mY + mYDirection + (mBallSize / 2);
    int wSpeed = 4;

    // check if there is a hit
    if (wXCheckpoint <= (iLeftRack.mX1 + 25) && wYCheckpoint < iLeftRack.mY2 && wYCheckpoint > iLeftRack.mY1)
    {
        mXDirection *= -1;
    }
    else if(wXCheckpoint >= (iRightRack.mX1 - 10) && wYCheckpoint < iRightRack.mY2 && wYCheckpoint > iRightRack.mY1)
    {
        mXDirection *= -1;
    }

    // check if ball is at top or bottom
    if(wYCheckpoint < 20 || wYCheckpoint > mGameBoardHeight)
    {
        mYDirection *= -1;
    }

    // TODO: Add logic for "new" ball if it went out

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
