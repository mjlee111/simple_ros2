#ifndef QNODE_H
#define QNODE_H

#include <QDebug>
#include <QImage>
#include <QObject>
#include <QThread>
#include <rclcpp/rclcpp.hpp>

class qnode : public QThread
{
    Q_OBJECT
public:
    qnode();
    void run() override;

private:
public slots:

private:
signals:
};

#endif
