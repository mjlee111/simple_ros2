#ifndef QNODE_H
#define QNODE_H

#include <QDebug>
#include <QImage>
#include <QObject>
#include <QThread>
#include <rclcpp/rclcpp.hpp>

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;

Q_SIGNALS:
  void rosShutDown();
};

#endif
