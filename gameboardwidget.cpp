#include "gameboardwidget.h"
#include <QPainter>


GameBoardWidget::~GameBoardWidget()
{

}

void GameBoardWidget::updateGameBoard()
{
    update();
}

void GameBoardWidget::leftRackMove(int iDirection)
{
    mLeftRack.mY1 += iDirection;
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;
    update();
}

void GameBoardWidget::rightRackMove(int iDirection)
{
    mRightRack.mY1 += iDirection;
    mRightRack.mY2 = mRightRack.mY1 + mRackLength;
    update();
}

void GameBoardWidget::setRacks(QSize iSize)
{
    mRackPenSize = 20;
    mRackLength = 90;

    mRightRack.mX1 = iSize.width() - (mRackPenSize * 2) + 5;
    mRightRack.mY1 = 1;
    mRightRack.mX2 = mRightRack.mX1;
    mRightRack.mY2 = mRightRack.mY1 + mRackLength;

    mLeftRack.mX1 = (mRackPenSize / 2) + 2;
    mLeftRack.mY1 = 1;
    mLeftRack.mX2 = mLeftRack.mX1;
    mLeftRack.mY2 = mLeftRack.mY1 + mRackLength;

}

void GameBoardWidget::paintEvent(QPaintEvent */*event*/)
{
     QPainter painter(this);
     painter.save();
     painter.setPen(QPen(static_cast<QColor>(Qt::white), mRackPenSize, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));

     //painter.drawLine(5,7,25,30);
     painter.drawLine(mRightRack.mX1,mRightRack.mY1,mRightRack.mX2,mRightRack.mY2);
     painter.drawLine(mLeftRack.mX1,mLeftRack.mY1,mLeftRack.mX2,mLeftRack.mY2);

     painter.restore();

     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.setPen(palette().dark().color());
     painter.setBrush(Qt::NoBrush);
     painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
