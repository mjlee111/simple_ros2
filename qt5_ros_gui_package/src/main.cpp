#include <QApplication>
#include <QMovie>
#include <QPixmap>
#include <QSplashScreen>
#include <iostream>

#include "mainwindow.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
