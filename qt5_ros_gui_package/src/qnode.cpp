#include "qnode.h"
qnode::qnode()
{
  int argc = 0;
  char **argv = NULL;
  rclcpp::init(argc, argv);
}

void qnode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    loop_rate.sleep();
  }
  rclcpp::shutdown();
}