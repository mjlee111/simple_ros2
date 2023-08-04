#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include <serial/serial.h>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;
using namespace serial;

void serialReadThread();
void run();

Serial s;
mutex m;
bool serialRead = false;
queue<uint8_t> readByte;

const string& port = "/dev/ttyUSB0";
vector<uint8_t> packet;

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("SerialNode");
    s.setPort(port);
    s.setBaudrate(1000000);

    try
    {
        s.open();
    }
    catch(serial::IOException e)
    {
        cerr << "Port open Failed." + port << e.what() << endl;
        return false;
    }
    cout << "Port Opened" << endl;
    serialRead = true;
    thread readThread(serialReadThread);

    rclcpp::Rate loopRate(10);
    packet.push_back(0xFF);

    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        // put your spin code in here
        s.write(packet);
        loopRate.sleep();
    }
    serialRead = false;
    readThread.join();

    rclcpp::shutdown();
    return 0;
}

void serialReadThread()
{
  unsigned char readBuffer[100];
  while(serialRead)
  {
    try 
    {
      int size = s.available();
      if (size != 0) 
      {
        s.read(readBuffer, size); 

        m.lock(); 
        for(int i=0; i<size; i++) readByte.push(readBuffer[i]);
        m.unlock();
      }
    }
    catch (IOException e)
    {
      cerr << "Port disconnected. closing port(" << e.what() << ")." << endl;
      s.close();
    }

    this_thread::sleep_for(chrono::milliseconds(1)); 
  }
}