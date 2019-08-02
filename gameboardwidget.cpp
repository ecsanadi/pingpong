#include "gameboardwidget.h"
#include <QPainter>
#include <iostream>
#include <unistd.h>

GameBoardWidget::~GameBoardWidget()
{

}

void GameBoardWidget::updateGameBoard()
{
    //TODO: set rate and set the update of racks and ball dependent on the rate
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

    mBall.updateBallPosition(mLeftRack,mRightRack);

    update();

}


void GameBoardWidget::init(QSize iSize)
{
    mSize = iSize;
    mSize.setHeight(mSize.height() - 60);
    mSize.setWidth(mSize.width()-25);
    mRackPenSize = 20;
    mRackLength = 90;
    mRackSpeed = 4;
    mBallSize = 15;
    mBall.init(mSize, mBallSize);
    mBall.setBallPosition(mSize.width() / 2, mSize.height() / 2);

    mRightRack.mX1 = mSize.width() - mRackPenSize / 2;
    mRightRack.mY1 = 1;
    mRightRack.mX2 = mRightRack.mX1;
    mRightRack.mY2 = mRightRack.mY1 + mRackLength;

    mLeftRack.mX1 = (mRackPenSize / 2) + 2;
    mLeftRack.mY1 = 1;
    mLeftRack.mX2 = mLeftRack.mX1;
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;

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
     painter.setPen(QPen(static_cast<QColor>(Qt::white), mRackPenSize, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));

     checkPositions();

     // TODO: draw vertical line across the center of the gameboard
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
