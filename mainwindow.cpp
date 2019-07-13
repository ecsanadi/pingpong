#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow()
{
  myGameBoard = new GameBoardWidget;

  m_button_new = new QPushButton("New game", this);
  connect(m_button_new, SIGNAL (clicked()), this, SLOT (buttonNewGame()));

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addWidget(myGameBoard, 0, 0);
  mainLayout->addWidget(m_button_new, 0, 1);

  setLayout(mainLayout);

  setWindowTitle(tr("PingPong"));
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::buttonNewGame()
{
    //TODO
}
