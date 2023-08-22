#include "../inc/mainwindow.h"
#include "../res/ui_mainwindow.h"

#if defined(Q_OS_ANDROID)
#include <QtCore/qjniobject.h>
#include <QtCore/qcoreapplication.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
#if defined(Q_OS_ANDROID)
    androidMulticastController("acquire");
#endif
    ui->setupUi(this);

    //get and show our name
    hostName = QHostInfo::localHostName();
    ui->lineEdit->setText(hostName);
    qDebug() << "My name is: " << hostName;

    //bind and connect signals of our sockets
    udpSocket = new QUdpSocket(this);
    tcpServer = new QTcpServer(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &MainWindow::handleBroadcast);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::handleTcpConnection);
    
    //0.001% error handling :D
    if(!tcpServer->listen(QHostAddress::Any, 13378))
    {
        qDebug() << ("Couldn't start tcp server. Now other's can't connect to you!");
    }
    else
    {
        qDebug() << ("TCP server started successfully!");
    }

    //every 1 second we will broadcast ourself for everyone
    broadcastTimer = new QTimer(this);
    connect(broadcastTimer, &QTimer::timeout,
            this, &MainWindow::broadcast);
    broadcastTimer->start(1000);

    //share our name and QListWidget with deviceList
    deviceList.myName = hostName;
    deviceList.list = ui->listWidget;

    //every 1 sec QListWidget will be cleaned 
    autoDelete = new QTimer(this);
    connect(autoDelete, &QTimer::timeout,
            this, &MainWindow::autoDeleteSlot);
    autoDelete->start(1000);

    //connect selecting device from QListWidget
    connect(ui->listWidget, &QListWidget::itemPressed,
            this, &MainWindow::devicePicked);
}

MainWindow::~MainWindow()
{
#if defined(Q_OS_ANDROID)
    androidMulticastController("release");
#endif
    delete ui;
}

void MainWindow::broadcast(){
    QByteArray datagram = "SENDI" + hostName.toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void MainWindow::handleBroadcast(){
    QByteArray datagram;
    QHostAddress senderAddress;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress);
        QString message = QString::fromUtf8(datagram);
        if (message.startsWith("SENDI") and message != "SENDI" + hostName){
            message.remove(0,5);
            deviceList.addItem(message, senderAddress);

        }
    }
}

void MainWindow::connectBtnRls(){
    qDebug() << "Connect btn released!";
}

void MainWindow::devicePicked(QListWidgetItem* device){
    qDebug() << "device was selected" << device->text();
}

void MainWindow::handleTcpConnection(){

}

void MainWindow::changeNamePressed(){
    if (ui->lineEdit->isReadOnly()){
        ui->lineEdit->setReadOnly(false);
        ui->chngNmButton->setText("Готово!");
    }else{
        ui->lineEdit->setReadOnly(true);
        ui->chngNmButton->setText("Изменить");
        ui->lineEdit->setFocus();
        hostName = ui->lineEdit->text();
    }
}

void MainWindow::autoDeleteSlot(){
    deviceList.deleteTrash();
}


void MainWindow::androidMulticastController(const char* pMethodName){
    #if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject::callStaticMethod<void>("com/governikus/ausweisapp2/MulticastLockJniBridgeUtil",
                                              pMethodName,
                                              "(Landroid/content/Context;)V",
                                              QNativeInterface::QAndroidApplication::context());
    #endif
}

