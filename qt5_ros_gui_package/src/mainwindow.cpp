#include "mainwindow.h"
#include "mj_udp.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  initUi();
}

void MainWindow::initUi()
{
  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
  //  WriteSettings();
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow() { delete ui; }
