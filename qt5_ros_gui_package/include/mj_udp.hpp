/**
 * @file mj_udp.hpp
 * @author mjlee111
 * @brief
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MJ_UDP_H
#define MJ_UDP_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QMainWindow>
#include <QByteArray>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include "image_transport/image_transport.h"
#include "crc.h"

namespace udp
{
    using namespace cv;
    using namespace std;

    class UDP : public QMainWindow
    {
    public:
        bool connection = false;

        void udp_write_text(QString text, uint16_t port, QHostAddress address, QUdpSocket &socket)
        {
            QByteArray packet;
            packet.append(text);
            socket.writeDatagram(packet, address, port);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            packet.clear();
        }

        void udp_write_array(QByteArray text, uint16_t port, QHostAddress address, QUdpSocket &socket)
        {
            QByteArray packet;
            packet.append(text);
            socket.writeDatagram(packet, address, port);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            packet.clear();
        }

        bool crc8_check(const QByteArray &data)
        {
            uint8_t end = data.at(data.size() - 1);
            QByteArray dataWithoutEnd = data;
            dataWithoutEnd.remove(dataWithoutEnd.size() - 1, 1);

            if (end != CRC8(true).calculate(dataWithoutEnd))
            {
                return false;
            }
            else
            {
                return true;
            }
            dataWithoutEnd.clear();
        }

        void crc8_input(QByteArray &data)
        {
            uint8_t crc_result = CRC8(true).calculate(data);
            data.push_back(crc_result);
        }

    public slots:
        void udp_read(uint16_t port, QHostAddress &address, QUdpSocket &socket)
        {
            QByteArray buffer;
            buffer.resize(socket.pendingDatagramSize());
            socket.readDatagram(buffer.data(), buffer.size(), &address, &port);
            /*

            put your return code here ...

            */
            buffer.clear();
        }

        bool udp_check(uint16_t port, QHostAddress &address, QUdpSocket &socket)
        {
            QByteArray buffer;
            buffer.resize(socket.pendingDatagramSize());
            socket.readDatagram(buffer.data(), buffer.size(), &address, &port);

            if (buffer.at(0) == 'o' && buffer.at(1) == 'k')
            {
                QByteArray packet;
                packet.push_back("ok");
                socket.writeDatagram(packet, address, port);
                connection = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            else
            {
                QByteArray packet;
                packet.push_back("cl"); // connection lost
                socket.writeDatagram(packet, address, port);
                connection = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            buffer.clear();
            return connection;
        }

        void send_cam_img(vector<uchar> img, uint16_t port, QHostAddress &address, QUdpSocket &socket)
        {
            QByteArray array;
            for (auto val : img)
            {
                array.push_back(val);
            }

            int sendChk;
            sendChk = socket.writeDatagram(array.data(), array.size(), address, port);
            while (sendChk == -1)
            {
                sendChk = socket.writeDatagram(array.data(), array.size(), address, port);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            array.clear();
        }

        void read_cam_img(Mat img, uint16_t port, QHostAddress &address, QUdpSocket &socket)
        {
            QByteArray cam_buffer;
            cam_buffer.resize(socket.pendingDatagramSize());
            socket.readDatagram(cam_buffer.data(), cam_buffer.size(), &address, &port);

            std::vector<uchar> down_decoding(cam_buffer.begin(), cam_buffer.end());
            img = imdecode(Mat(down_decoding), cv::IMREAD_COLOR);
            cam_buffer.clear();
        }
    };
}

#endif
