#ifndef BALL_H
#define BALL_H

#include <QSize>

class Ball
{
public:
    Ball();
    int mX;
    int mY;
    int mXDirection;
    int mYDirection;

    void init(QSize iSize);

    void setBallPosition(int iX, int iY);
    void updateBallPosition();
};

#endif // BALL_H
