#include <utility>
#include "../inc/pelengator.h"

Pelengator::Pelengator(QObject *parent, QString my_name, QListWidget* list_widget) : QObject(parent), my_name(std::move(my_name)), ui_list_widget(list_widget) {
    android_multicast_acquire();
    device_list = new DeviceList(this, ui_list_widget, this->my_name, clear_delay);
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(45454, QUdpSocket::ShareAddress);
    connect(udp_socket, &QUdpSocket::readyRead,
            this, &Pelengator::handle_incoming_broadcast);
    broadcast_timer = new QTimer(this);
    connect(broadcast_timer, &QTimer::timeout, this, &Pelengator::broadcast);
    broadcast_timer->start(broadcast_delay);
    broadcast();
}

void Pelengator::broadcast() {
    QByteArray datagram = "SENDI" + my_name.toUtf8();
    udp_socket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void Pelengator::handle_incoming_broadcast() {
    QByteArray datagram;
    QHostAddress senderAddress;
    while (udp_socket->hasPendingDatagrams()) {
        datagram.resize(int(udp_socket->pendingDatagramSize()));
        udp_socket->readDatagram(datagram.data(), datagram.size(), &senderAddress);
        QString message = QString::fromUtf8(datagram);
        if (message.startsWith("SENDI") and message != "SENDI" + my_name){
            message.remove(0,5);
            device_list->addItem(message, senderAddress);
            qDebug() << "Broadcast incoming: " << message;
        }
    }
}

QHostAddress Pelengator::get_address(QListWidgetItem *device) {
    return device_list->getAddress(device);
}

Pelengator::~Pelengator() {
    android_multicast_release();
}

[[maybe_unused]] void Pelengator::android_multicast_acquire() {
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject::callStaticMethod<void>("com/governikus/ausweisapp2/MulticastLockJniBridgeUtil",
                                       "acquire",
                                       "(Landroid/content/Context;)V",
                                       QNativeInterface::QAndroidApplication::context());
#endif
}
[[maybe_unused]] void Pelengator::android_multicast_release() {
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject::callStaticMethod<void>("com/governikus/ausweisapp2/MulticastLockJniBridgeUtil",
                                       "release",
                                       "(Landroid/content/Context;)V",
                                       QNativeInterface::QAndroidApplication::context());
#endif
}


