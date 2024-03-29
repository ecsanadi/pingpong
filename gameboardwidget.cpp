#include "gameboardwidget.h"
#include <QPainter>
#include <iostream>
#include <unistd.h>
#include <QDebug>

GameBoardWidget::~GameBoardWidget()
{

}

void GameBoardWidget::setGameSpeed(int iSpeedLevel)
{
    if(iSpeedLevel > 5)
    {
        mGameSpeed = 5;
    }

    switch(iSpeedLevel)
    {
    case 1:
        mBallUpdateSpeed = 6;
        mRackUpdateSpeed = 5;
        break;
    case 2:
        mBallUpdateSpeed = 5;
        mRackUpdateSpeed = 4;
        break;
    case 3:
        mBallUpdateSpeed = 4;
        mRackUpdateSpeed = 3;
        break;
    case 4:
        mBallUpdateSpeed = 3;
        mRackUpdateSpeed = 2;
        break;
    case 5:
        mBallUpdateSpeed = 2;
        mRackUpdateSpeed = 1;
        break;
    default:
        mBallUpdateSpeed = 1;
        mRackUpdateSpeed = 1;

    }
}

void GameBoardWidget::updateGameBoard()
{
    static int wRackUpdateCounter = mRackUpdateSpeed;
    static int wBallUpdateCounter = mBallUpdateSpeed;
    static bool isUpdate = false;

    if(mBall.getIsBallOut())
    {
        resetBallPosition();
    }

    ms_current = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    if(ms_current - ms_last > ms_delta)
    {
        ms_last = ms_current;
        setGameSpeed(++mGameSpeed);
    }

    if (wRackUpdateCounter <= 0 )
    {
        wRackUpdateCounter = mRackUpdateSpeed;
        if(mLMovingUp)
        {
            mLeftRack.mY1 -= mRackSpeed;
            mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;
        }
        if(mLMovingDo)
        {
            mLeftRack.mY1 += mRackSpeed;
            mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;
        }
        if(mRMovingUp)
        {
            mRightRack.mY1 -= mRackSpeed;
            mRightRack.mY2 = mRightRack.mY1 + mRackLength;
        }
        if(mRMovingDo)
        {
            mRightRack.mY1 += mRackSpeed;
            mRightRack.mY2 = mRightRack.mY1 + mRackLength;
        }
        isUpdate = true;
    }
    else
    {
        wRackUpdateCounter--;
    }

    if (wBallUpdateCounter <= 0)
    {
        wBallUpdateCounter = mBallUpdateSpeed;
        mBall.updateBallPosition(mLeftRack,mRightRack, mLScore, mRScore);
        isUpdate = true;
    }
    else
    {
        wBallUpdateCounter--;
    }

    if(isUpdate)
    {
        isUpdate = false;
        update();
    }

}

void GameBoardWidget::resetGameBoard()
{
    init(mSize);
    update();
}


void GameBoardWidget::resetBallPosition()
{
    mBall.init(mSize, mBallSize);
    mBall.setBallPosition(mSize.width() / 2, mSize.height() / 2);
}

void GameBoardWidget::init(QSize iSize)
{
    if (mSize != iSize)
    {
        mSize = iSize;
        mSize.setHeight(mSize.height() - 60);
        mSize.setWidth(mSize.width()-25);
    }

    ms_current = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    ms_last = ms_current;
    ms_delta = std::chrono::milliseconds(60000);
    mLScore = 0;
    mRScore = 0;
    mRackPenSize = 20;
    mRackLength = 90;
    mRackSpeed = 3;
    mBallSize = 15;
    mGameSpeed = 1;
    setGameSpeed(mGameSpeed);
    resetBallPosition();

    mRightRack.mX1 = mSize.width() - mRackPenSize / 2;
    mRightRack.mY1 = (mSize.height() / 2) - (mRackLength / 2);
    mRightRack.mX2 = mRightRack.mX1;
    mRightRack.mY2 = mRightRack.mY1 + mRackLength;

    mLeftRack.mX1 = (mRackPenSize / 2) + 2;
    mLeftRack.mY1 = mSize.height() / 2 - (mRackLength / 2);
    mLeftRack.mX2 = mLeftRack.mX1;
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;

    mCenterLine.mX1 = mSize.width() / 2;
    mCenterLine.mX2 = mCenterLine.mX1;
    mCenterLine.mY1 = 1;
    mCenterLine.mY2 = mSize.height();

}

void GameBoardWidget::checkPositions()
{
    if (mLeftRack.mY1 <= 0)
    {
        mLeftRack.mY1 = 1;
    }
    if(mLeftRack.mY1 + mRackLength > (mSize.height()))
    {
        mLeftRack.mY1 -= mRackSpeed;
    }
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;

    if (mRightRack.mY1 <= 0)
    {
        mRightRack.mY1 = 1;
    }
    if(mRightRack.mY1 + mRackLength > (mSize.height()))
    {
        mRightRack.mY1 -= mRackSpeed;
    }
    mRightRack.mY2 = mRightRack.mY1 + mRackLength;
}

void GameBoardWidget::paintEvent(QPaintEvent */*event*/)
{
     QPainter painter(this);
     painter.save();

     checkPositions();

     // TODO: consider one player mode selection and paint a wall instead of one rack

     painter.setPen(QPen(static_cast<QColor>(Qt::white), mRackPenSize/3, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
     painter.drawLine(mCenterLine.mX1, mCenterLine.mY1, mCenterLine.mX2, mCenterLine.mY2);
     painter.setPen(QPen(static_cast<QColor>(Qt::white), mRackPenSize, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
     painter.drawLine(mRightRack.mX1,mRightRack.mY1,mRightRack.mX2,mRightRack.mY2);
     painter.drawLine(mLeftRack.mX1,mLeftRack.mY1,mLeftRack.mX2,mLeftRack.mY2);

     painter.setPen(QPen(static_cast<QColor>(Qt::white), mBallSize, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
     painter.drawPoint(mBall.getBallX(), mBall.getBallY());

     painter.restore();

     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.setPen(palette().dark().color());
     painter.setBrush(Qt::NoBrush);
     painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
