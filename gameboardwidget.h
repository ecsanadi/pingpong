#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include "line.h"
#include "point.h"
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
    bool mRMoving = false;
    bool mLMoving = false;


public slots:
    void updateGameBoard();
    void leftRackMove(int iDirection);
    void rightRackMove(int iDirection);

protected:
    void paintEvent(QPaintEvent *event) override;
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);

private:
    int mRackPenSize;
    int mRackLength;
    Point mBall;
    QSize mSize;
    Line mRightRack;
    Line mLeftRack;

    void checkPositions();
};

#endif // GAMEBOARDWIDGET_H
