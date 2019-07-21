#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow()
{
  myGameBoard = new GameBoardWidget;

  m_button_new = new QPushButton("New game", this);
  connect(m_button_new, SIGNAL (clicked()), this, SLOT (buttonNewGame()));

  QPalette pal = palette();

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  myGameBoard->setAutoFillBackground(true);
  myGameBoard->setPalette(pal);

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addWidget(myGameBoard, 0, 0);
  mainLayout->addWidget(m_button_new, 1, 0);

  setLayout(mainLayout);

  buttonNewGame();

  setWindowTitle(tr("PingPong"));

  centerAndResize();

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::buttonNewGame()
{
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

void MainWindow::leftRackUp()
{
    myGameBoard->leftRackMove(UP);
}

void MainWindow::leftRackDown()
{
    myGameBoard->leftRackMove(DOWN);
}

void MainWindow::rightRackUp()
{
    myGameBoard->rightRackMove(UP);
}

void MainWindow::rightRackDown()
{
    myGameBoard->rightRackMove(DOWN);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W )
    {
        emit leftRackUp(); // connected elsewhere
    }
    if (event->key() == Qt::Key_S)
    {
        emit leftRackDown();
    }
    if (event->key() == Qt::Key_O)
    {
        emit rightRackUp();
    }
    if(event->key() == Qt::Key_L)
    {
        emit rightRackDown();
    }

}
