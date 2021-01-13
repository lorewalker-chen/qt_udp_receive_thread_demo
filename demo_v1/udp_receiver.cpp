#include "udp_receiver.h"

#include <QtNetwork>

UdpReceiver::UdpReceiver(QObject* parent) : QObject(parent) {
    local_net_parameter_.ip = "127.0.0.1";
    local_net_parameter_.port = 8080;
    qDebug() << "UdpReceiver constructor: " << QThread::currentThreadId();
}

UdpReceiver::~UdpReceiver() {
    delete socket_;
}

void UdpReceiver::SetLocalNetParameter(NetParameter parameter) {
    local_net_parameter_.ip = parameter.ip;
    local_net_parameter_.port = parameter.port;
}

UdpReceiver::NetParameter UdpReceiver::GetLocalNetParameter() {
    return local_net_parameter_;
}
//初始化socket，绑定本机ip和端口号，连接信号和槽
void UdpReceiver::InitSocket() {
    qDebug() << "UdpReceiver InitSocket: " << QThread::currentThreadId();
    socket_ = new QUdpSocket;
    socket_->bind(QHostAddress(local_net_parameter_.ip),
                  local_net_parameter_.port,
                  QUdpSocket::ShareAddress);
    connect(socket_, &QUdpSocket::readyRead, this, &UdpReceiver::ReceiveData);
}
//取出管道中的数据，并发送信号
void UdpReceiver::ReceiveData() {
    qDebug() << "UdpReceiver ReceiveData: " << QThread::currentThreadId();
    while (socket_->hasPendingDatagrams()) {
        QByteArray array;
        array.resize(socket_->pendingDatagramSize());
        socket_->readDatagram(array.data(), array.size());
        emit ReceivedData(array);
    }
}
