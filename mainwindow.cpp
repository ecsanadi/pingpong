#include "mainwindow.h"
#include <QtWidgets>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow()
{
  myGameBoard = new GameBoardWidget;

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

  mainLayout = new QGridLayout;

  mainLayout->addWidget(myGameBoard, 0, 0);
  mainLayout->addWidget(m_button_new, 1, 0,Qt::AlignRight);
  mainLayout->addWidget(mScoreLabel, 1,0 , Qt::AlignLeft);
  mainLayout->addWidget(mTimeElapsed, 1, 0, Qt::AlignCenter);

  setLayout(mainLayout);

  buttonNewGame();

  mCountdown = true;

  setWindowTitle(tr("PingPong"));

  centerAndResize();

}

MainWindow::~MainWindow()
{
    delete myGameBoard;
    delete m_button_new;
    delete timer;
    delete elapse;
    delete mScoreLabel;
    delete mTimeElapsed;
    delete mainLayout;
}

QString MainWindow::timeElapsed()
{
    static int counter = -4;

    if(mCountdown)
    {
        mCountdown = false;
        counter = -4;
    }

    counter++;

    if(counter > 0)
    {
        return QString("%1:%2").arg( counter / 60, 2, 10, QChar('0'))
                                      .arg(counter % 60, 2, 10, QChar('0'));
    }
    else if(counter < 0)
    {
        return QString("-%1:%2").arg( 0, 2, 10, QChar('0'))
                                      .arg(abs(counter), 2, 10, QChar('0'));
    }
    else
    {
        continueGame();
    }

    return QString("%1:%2").arg( 0, 2, 10, QChar('0'))
                                  .arg(0, 2, 10, QChar('0'));
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
    mCountdown = true;
    pauseGame();
    myGameBoard->resetGameBoard();    
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
    paused = true;
    timer->stop();
}

void MainWindow::continueGame()
{
    paused = false;
    timer->start();
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

void MainWindow::checkWindowSize()
{
    static QSize size = this->size();
    QSize newSize = this->size();
    if (newSize != size)
    {
        myGameBoard->init(newSize);
    }

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(!event->isAutoRepeat())
    {
        if( event->key() == Qt::Key_W )
        {
            myGameBoard->mLMovingUp = true;
        }
        if (event->key() == Qt::Key_S)
        {
            myGameBoard->mLMovingDo = true;
        }
        if (event->key() == Qt::Key_O)
        {
            myGameBoard->mRMovingUp = true;
        }
        if(event->key() == Qt::Key_L)
        {
            myGameBoard->mRMovingDo = true;
        }
        if(event->key() == Qt::Key_P)
        {
            // TODO: catch space instead of P
            std::cout << "SPACE" << std::endl;
            if(paused)
            {
                continueGame();
            }
            else
            {
                pauseGame();
            }
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if( event->key() == Qt::Key_W )
        {
            myGameBoard->mLMovingUp = false;
        }
        if (event->key() == Qt::Key_S)
        {
            myGameBoard->mLMovingDo = false;
        }
        if (event->key() == Qt::Key_O)
        {
            myGameBoard->mRMovingUp = false;
        }
        if(event->key() == Qt::Key_L)
        {
            myGameBoard->mRMovingDo = false;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    checkWindowSize();
    QWidget::resizeEvent(event);

}
