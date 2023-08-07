
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QMainWindow>

#include "QTimer"
#include "QIcon"
#include "qnode.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  qnode *commNode;

public slots:

private:
  void initUi();
  void closeEvent(QCloseEvent *event);

private:
  Ui::MainWindowDesign *ui;
};
#endif // MAINWINDOW_H
