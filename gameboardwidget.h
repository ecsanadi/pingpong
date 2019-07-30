#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include "line.h"
#include "point.h"
#include "ball.h"
#include <QKeyEvent>

class GameBoardWidget : public QWidget
{
public:
    GameBoardWidget(QWidget *parent = 0) :
        QWidget(parent)
    {

    }

    ~GameBoardWidget();
    void init(QSize iSize);
    bool mRMovingUp = false;
    bool mLMovingUp = false;
    bool mRMovingDo = false;
    bool mLMovingDo = false;


public slots:
    void updateGameBoard();
    void leftRackMove(int iDirection);
    void rightRackMove(int iDirection);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mRackPenSize;
    int mRackLength;
    Ball mBall;
    QSize mSize;
    Line mRightRack;
    Line mLeftRack;
    int mRackSpeed;
    void checkPositions();
    int mBallSize;
};

#endif // GAMEBOARDWIDGET_H
