//
// Created by rups1k on 9/15/23.
//

#ifndef SEND_IT_PELENGATOR_H
#define SEND_IT_PELENGATOR_H

#include "devicelist.h"

#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QListWidget>

class Pelengator : public QObject{
    Q_OBJECT
private:
    QTimer* broadcast_delay_timer;
    QTimer* clear_devices_delay_timer;
    QUdpSocket* udp_socket;
    QString my_name;
    QListWidget* ui_list_widget;
    DeviceList* device_list;

    void broadcast();
    void handle_incoming_broadcast();
    void clear_device_list();
public:
    std::chrono::milliseconds clear_delay{2000};
    std::chrono::milliseconds broadcast_delay{1000};

    explicit Pelengator(QObject* parent, QString my_name, QListWidget* list_widget);
};


#endif //SEND_IT_PELENGATOR_H
