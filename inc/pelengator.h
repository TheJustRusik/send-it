#pragma once

#include "devicelist.h"

#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QListWidget>

namespace chr = std::chrono;

#if defined(Q_OS_ANDROID)
    #include <QtCore/qjniobject.h>
    #include <QtCore/qcoreapplication.h>
#endif

class Pelengator : public QObject{
    Q_OBJECT
private:
    QTimer* broadcast_timer;
    QUdpSocket* udp_socket;
    QString my_name;
    QListWidget* ui_list_widget;
    DeviceList* device_list;


    [[maybe_unused]] void android_multicast_acquire();
    [[maybe_unused]] void android_multicast_release();


public:
    chr::milliseconds broadcast_delay{1000};
    chr::milliseconds clear_delay{2000};

    explicit Pelengator(QObject* parent, QString my_name, QListWidget* list_widget);
    ~Pelengator() override;
    QHostAddress get_address(QListWidgetItem* device);
private slots:
    void broadcast();
    void handle_incoming_broadcast();
};