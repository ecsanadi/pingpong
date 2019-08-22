#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "gameboardwidget.h"
#include <QLabel>

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
   QLabel *mScoreLabel;
   void centerAndResize();
   const int UP = -4;
   const int DOWN = 4;
   void countDown();
   QString getScoreLabelText();

protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);

private slots:
    void buttonNewGame();
    void updateGameBoard();
};

#endif // MAINWINDOW_H
