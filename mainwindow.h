#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "gameboardwidget.h"
#include <QLabel>
#include <QTime>
#include <QLayout>

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
   QLabel *mTimeElapsed;
   void centerAndResize();
   void checkWindowSize();
   const int UP = -4;
   const int DOWN = 4;
   QString timeElapsed();
   QString getScoreLabelText();
   QTime mGameTime;
   QTimer *timer;
   QTimer *elapse;
   QGridLayout *mainLayout;
   void pauseGame();
   void continueGame();
   bool paused;
   bool mCountdown;

protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
   void resizeEvent(QResizeEvent *event);

private slots:
    void buttonNewGame();
    void updateGameBoard();
    void updateTimerLabel();

};

#endif // MAINWINDOW_H
