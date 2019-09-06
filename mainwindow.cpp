#include "mainwindow.h"
#include <QtWidgets>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow()
{
  myGameBoard = new GameBoardWidget;

   ///*myGameBoard*/this->setFocusPolicy(Qt::NoFocus);


  m_button_new = new QPushButton("New game", this);
  connect(m_button_new, SIGNAL (clicked()), this, SLOT (buttonNewGame()));

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateGameBoard()));
  timer->start(5);

  elapse = new QTimer(this);
  connect(elapse, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
  elapse->start(1000);

  QPalette pal = palette();

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  myGameBoard->setAutoFillBackground(true);
  myGameBoard->setPalette(pal);

  mScoreLabel = new QLabel(this);
  mScoreLabel->setText( getScoreLabelText() );

  mTimeElapsed = new QLabel(this);

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addWidget(myGameBoard, 0, 0);
  mainLayout->addWidget(m_button_new, 1, 0,Qt::AlignRight);
  mainLayout->addWidget(mScoreLabel, 1,0 , Qt::AlignLeft);
  mainLayout->addWidget(mTimeElapsed, 1, 0, Qt::AlignCenter);

  setLayout(mainLayout);

  paused = false;

  buttonNewGame();

  mGameTime.start();

  setWindowTitle(tr("PingPong"));

  centerAndResize();



}

MainWindow::~MainWindow()
{
    //TODO: check what should be free
}

QString MainWindow::timeElapsed()
{

    return QString("%1:%2").arg( mGameTime.elapsed() / 60000        , 2, 10, QChar('0'))
                                  .arg((mGameTime.elapsed() % 60000) / 1000, 2, 10, QChar('0'));

}

void MainWindow::updateTimerLabel()
{
   mTimeElapsed->clear();
   mTimeElapsed->setText(timeElapsed());
}

QString MainWindow::getScoreLabelText()
{
    QString wScoreText;
    wScoreText.append( "Score: " );
    wScoreText.append(QString::number(myGameBoard->getLScore()));
    wScoreText.append( " : " );
    wScoreText.append(QString::number(myGameBoard->getRScore()));
    return wScoreText;
}

void MainWindow::buttonNewGame()
{
    myGameBoard->resetGameBoard();
    mGameTime.start();
    emit updateGameBoard();
}

void MainWindow::updateGameBoard()
{
    mScoreLabel->clear();
    mScoreLabel->setText( getScoreLabelText() );
    myGameBoard->updateGameBoard();
}

void MainWindow::pauseGame()
{
    timer->stop();
    elapse->stop();

}

void MainWindow::continueGame()
{
    timer->start();
    elapse->start();

}

void MainWindow::centerAndResize() {
    // get the dimension available on this screen
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.6; // 90% of the screen size
    height *= 0.8; // 90% of the screen size
    qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( width, height );

    myGameBoard->init(newSize);

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(!event->isAutoRepeat())
    {
        std::cout << " Key is pressed: " ;
        if( event->key() == Qt::Key_W )
        {
            std::cout << "W" << std::endl;
            myGameBoard->mLMovingUp = true;
        }
        if (event->key() == Qt::Key_S)
        {
            std::cout << "S" << std::endl;
            myGameBoard->mLMovingDo = true;
        }
        if (event->key() == Qt::Key_O)
        {
            std::cout << "O" << std::endl;
            myGameBoard->mRMovingUp = true;
        }
        if(event->key() == Qt::Key_L)
        {
            std::cout << "L" << std::endl;
            myGameBoard->mRMovingDo = true;
        }
        if(event->key() == Qt::Key_P)
        {
            // TODO: catch space instead of P
            std::cout << "SPACE" << std::endl;
            if(paused)
            {
                paused = false;
                continueGame();
            }
            else
            {
                paused = true;
                pauseGame();
            }
        }
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        std::cout << "Key is released: " ;
        if( event->key() == Qt::Key_W )
        {
            std::cout << "W" << std::endl;
            myGameBoard->mLMovingUp = false;
        }
        if (event->key() == Qt::Key_S)
        {
            std::cout << "S" << std::endl;
            myGameBoard->mLMovingDo = false;
        }
        if (event->key() == Qt::Key_O)
        {
            std::cout << "O" << std::endl;
            myGameBoard->mRMovingUp = false;
        }
        if(event->key() == Qt::Key_L)
        {
            std::cout << "L" << std::endl;
            myGameBoard->mRMovingDo = false;
        }
    }


}
