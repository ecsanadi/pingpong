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
    mIsBallOut = false;

}

void Ball::setBallPosition(int x, int y)
{
    mX = x;
    mY = y;
}

void Ball::updateBallPosition(Line iLeftRack, Line iRightRack, int &iLScore, int &iRScore)
{    
    int wBallSpeed = 3;

    int wXCheckpoint = mX + mXDirection + (mBallSize / 2);
    int wXLeftCheckpoint = mX + (mXDirection * wBallSpeed)  - (mBallSize / 2);
    int wYTopCheckpoint = mY + mYDirection - (mBallSize / 2);
    int wYBottomCheckpoint = mY + mYDirection + (mBallSize / 2);

    // check if there is a hit
    if (wXLeftCheckpoint <= (iLeftRack.mX1 + 10)
        && wYTopCheckpoint < iLeftRack.mY2
        && wYBottomCheckpoint > iLeftRack.mY1)
    {
        mXDirection *= -1;
        iLScore++;
    }
    else if(wXCheckpoint == (iRightRack.mX1 - 10)
            && wYTopCheckpoint < iRightRack.mY2
            && wYBottomCheckpoint > iRightRack.mY1)
    {
        mXDirection *= -1;
        iRScore++;
    }

    // check if ball is at top or bottom
    if(wYTopCheckpoint < 1 || wYBottomCheckpoint > mGameBoardHeight)
    {
        mYDirection *= -1;
    }

    // check if ball went out
    if(wXLeftCheckpoint < (iLeftRack.mX1 ) || wXCheckpoint > (iRightRack.mX1 - 10))
    {
        mIsBallOut = true;
    }

    mX += (mXDirection * wBallSpeed);
    mY += (mYDirection * wBallSpeed);
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
