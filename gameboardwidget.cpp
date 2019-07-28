#include "gameboardwidget.h"
#include <QPainter>
#include <iostream>
#include <unistd.h>

GameBoardWidget::~GameBoardWidget()
{

}

void GameBoardWidget::updateGameBoard()
{
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

    //TODO: update ball position here

    update();

}


void GameBoardWidget::init(QSize iSize)
{
    mSize = iSize;
    mRackPenSize = 20;
    mRackLength = 90;
    mRackSpeed = 4;

    mRightRack.mX1 = mSize.width() - (mRackPenSize * 2) + 5;
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
    if(mLeftRack.mY1 + mRackLength > (mSize.height() - 60))
    {
        mLeftRack.mY1 -= mRackSpeed;
    }
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;

    if (mRightRack.mY1 <= 0)
    {
        mRightRack.mY1 = 1;
    }
    if(mRightRack.mY1 + mRackLength > (mSize.height() - 60))
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

     //painter.drawLine(5,7,25,30);
     painter.drawLine(mRightRack.mX1,mRightRack.mY1,mRightRack.mX2,mRightRack.mY2);
     painter.drawLine(mLeftRack.mX1,mLeftRack.mY1,mLeftRack.mX2,mLeftRack.mY2);

     painter.restore();

     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.setPen(palette().dark().color());
     painter.setBrush(Qt::NoBrush);
     painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
