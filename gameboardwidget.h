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
    void setRacks(QSize iSize);

public slots:
    void updateGameBoard();
    void leftRackMove();
    void rightRackMove();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Line mRightRack;
    Line mLeftRack;
    int mRackPenSize;
    int mRackLength;
    Point mBall;
};

#endif // GAMEBOARDWIDGET_H
