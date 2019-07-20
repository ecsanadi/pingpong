#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "gameboardwidget.h"

class GameBoardWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
   MainWindow();
    ~MainWindow();

private:
   GameBoardWidget *myGameBoard;
   QPushButton *m_button_new;
   void centerAndResize();
   const int UP = -4;
   const int DOWN = 4;

protected:
   void keyPressEvent(QKeyEvent *event) override;

private slots:
    void buttonNewGame();
    void leftRackUp();
    void leftRackDown();
    void rightRackUp();
    void rightRackDown();
};

#endif // MAINWINDOW_H
