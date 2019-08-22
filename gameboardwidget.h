#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include "line.h"
#include "point.h"
#include "ball.h"
#include <QKeyEvent>
#include <chrono>

using namespace std::chrono;

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
    int getLScore(){return mLScore;}
    int getRScore(){return mRScore;}


public slots:
    void updateGameBoard();
    void resetGameBoard();
    void leftRackMove(int iDirection);
    void rightRackMove(int iDirection);
    void setGameSpeed(int iSpeedLevel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mRackPenSize;
    int mRackLength;
    Ball mBall;
    QSize mSize;
    Line mRightRack;
    Line mLeftRack;
    Line mCenterLine;
    int mRackSpeed;
    void checkPositions();
    int mBallSize;
    bool mIsUpdate;
    int mBallUpdateSpeed;
    int mRackUpdateSpeed;
    int mGameSpeed;
    milliseconds ms_current;
    milliseconds ms_last;
    milliseconds ms_delta;
    int mLScore;
    int mRScore;
};

#endif // GAMEBOARDWIDGET_H
