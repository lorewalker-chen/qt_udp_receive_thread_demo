#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class QThread;
class UdpReceiver;
class Dialog : public QDialog {
    Q_OBJECT

  public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();

  private slots:
    void ReceivedData(QByteArray array);

  private:
    void InitAll();

    Ui::Dialog* ui;
    QThread* thread_;//线程管理类
};
#endif // DIALOG_H
