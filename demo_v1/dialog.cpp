#include "dialog.h"
#include "ui_dialog.h"
#include "udp_receiver.h"

#include <QThread>
#include <QDebug>

Dialog::Dialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Dialog) {
    ui->setupUi(this);
    qDebug() << "main: " << QThread::currentThreadId();
    InitAll();
}

Dialog::~Dialog() {
    thread_->quit();
    thread_->wait();
    thread_->deleteLater();
    delete ui;
}

void Dialog::ReceivedData(QByteArray array) {
    ui->textEdit->append(array);
}

void Dialog::InitAll() {
    thread_ = new QThread;
    UdpReceiver* receiver_ = new UdpReceiver;
    //连接线程的started()信号到初始化socket槽，实现线程启动即初始化socket
    connect(thread_, &QThread::started, receiver_, &UdpReceiver::InitSocket);
    //线程结束receiver类自动释放
    connect(thread_, &QThread::finished, receiver_, &UdpReceiver::deleteLater);
    //接收到的数据发送信号到主线程处理
    connect(receiver_, &UdpReceiver::ReceivedData, this, &Dialog::ReceivedData);
    //移动到线程管理类
    receiver_->moveToThread(thread_);
    thread_->start();
    //获取当前监听的本机网络，并显示到界面
    UdpReceiver::NetParameter net_parameter;
    net_parameter = receiver_->GetLocalNetParameter();
    ui->lineEdit_local_ip->setText(net_parameter.ip);
    ui->lineEdit_local_port->setText(QString::number(net_parameter.port));
}

