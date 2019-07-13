#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>

class GameBoardWidget : public QWidget
{
public:
    GameBoardWidget(QWidget *parent = 0) :
        QWidget(parent)
    {

    }

    ~GameBoardWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GAMEBOARDWIDGET_H
