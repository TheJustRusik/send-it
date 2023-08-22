#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtCore>
#include "devicelist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QUdpSocket* udpSocket = nullptr;
    QTcpSocket* tcpSocket = nullptr;
    QTcpServer* tcpServer = nullptr;
    QString hostName;
    QTimer* broadcastTimer;
    QTimer* autoDelete;
    DeviceList deviceList;
private:
    Ui::MainWindow *ui;
    void androidMulticastController(const char* pMethodName);
private slots:
    void broadcast();
    void handleBroadcast();
    void handleTcpConnection();
    void autoDeleteSlot();
    void changeNamePressed();
    void connectBtnRls();
    void devicePicked(QListWidgetItem* device);
};
#endif // MAINWINDOW_H
