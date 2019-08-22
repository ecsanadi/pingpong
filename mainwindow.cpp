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

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateGameBoard()));
  timer->start(5);

  QPalette pal = palette();

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  myGameBoard->setAutoFillBackground(true);
  myGameBoard->setPalette(pal);

  mScoreLabel = new QLabel(this);
  mScoreLabel->setText( getScoreLabelText() );

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addWidget(myGameBoard, 0, 0);
  mainLayout->addWidget(m_button_new, 1, 0,Qt::AlignRight);
  mainLayout->addWidget(mScoreLabel, 1,0 , Qt::AlignLeft);

  setLayout(mainLayout);

  buttonNewGame();

  setWindowTitle(tr("PingPong"));

  centerAndResize();

}

MainWindow::~MainWindow()
{
    //TODO: check what should be free
}

void MainWindow::countDown()
{
    //TODO: display game time
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
    emit updateGameBoard();
}

void MainWindow::updateGameBoard()
{
    mScoreLabel->clear();
    mScoreLabel->setText( getScoreLabelText() );
    myGameBoard->updateGameBoard();
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
