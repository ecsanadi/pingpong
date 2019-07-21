#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include "line.h"
#include "point.h"

class GameBoardWidget : public QWidget
{
public:
    GameBoardWidget(QWidget *parent = 0) :
        QWidget(parent)
    {

    }

    ~GameBoardWidget();
    void init(QSize iSize);

    Line mRightRack;
    Line mLeftRack;

    void checkPositions();

public slots:
    void updateGameBoard();
    void leftRackMove(int iDirection);
    void rightRackMove(int iDirection);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mRackPenSize;
    int mRackLength;
    Point mBall;
    QSize mSize;
};

#endif // GAMEBOARDWIDGET_H
