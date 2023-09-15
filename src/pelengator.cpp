//
// Created by rups1k on 9/15/23.
//

#include <utility>

#include "../inc/pelengator.h"



Pelengator::Pelengator(QObject *parent, QString my_name, QListWidget* list_widget) : QObject(parent), my_name(std::move(my_name)), ui_list_widget(list_widget) {
    device_list = new DeviceList(ui_list_widget, this->my_name);
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(45454, QUdpSocket::ShareAddress);
    connect(udp_socket, &QUdpSocket::readyRead,
            this, &Pelengator::handle_incoming_broadcast);
    broadcast_delay_timer = new QTimer(this);
    connect(broadcast_delay_timer, &QTimer::timeout, this, &Pelengator::broadcast);
    broadcast_delay_timer->start(broadcast_delay);
    broadcast();
    clear_devices_delay_timer = new QTimer(this);
    connect(clear_devices_delay_timer, &QTimer::timeout, this, &Pelengator::clear_device_list);
    clear_devices_delay_timer->start(clear_delay);
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
            qDebug() << "Broadcast incoming: " << message << "\n";
        }
    }
}

void Pelengator::clear_device_list() {
    device_list->deleteTrash();
}

