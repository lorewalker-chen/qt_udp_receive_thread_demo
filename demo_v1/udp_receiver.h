#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>

class QUdpSocket;
class UdpReceiver : public QObject {
    Q_OBJECT
  public:
    explicit UdpReceiver(QObject* parent = nullptr);
    ~UdpReceiver();

    struct NetParameter {
        QString ip;
        int port;
    };

    void SetLocalNetParameter(NetParameter parameter);
    NetParameter GetLocalNetParameter();

  public slots:
    /*
     * 初始化需要声明为槽，
     * 将该类moveToThread时，
     * 该类中的所有槽函数在新线程中运行，
     * 初始化声明为普通函数会导致
     * socket的初始化和使用不在同一个线程
     */
    void InitSocket();//初始化udp socket

  private slots:
    void ReceiveData();//取出管道的数据

  private:
    QUdpSocket* socket_;
    NetParameter local_net_parameter_;

  signals:
    void ReceivedData(QByteArray array);
};

#endif // UDPRECEIVER_H
