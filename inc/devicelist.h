#pragma once

#include <QString>
#include <QTimer>
#include <QTime>
#include <QHash>
#include <QListWidget>
#include <QHostAddress>
#include <QMainWindow>
#include <QtNetwork>
#include <QtCore>

namespace chr = std::chrono;

struct TimeAndAddress{
    QTime time;
    QHostAddress address;
};

class DeviceList : public QObject{
    Q_OBJECT
private:
    QHash<QListWidgetItem*, TimeAndAddress> devices;
    QListWidget* list;
    QTimer* clear_timer;
    chr::milliseconds clear_delay;
public:
    DeviceList(QObject* parent, QListWidget* list, QString  name, chr::milliseconds clear_delay_ms);
    QString myName;
    void addItem(const QString& name, const QHostAddress& address);
    QHostAddress getAddress(QListWidgetItem* device);
private slots:
    void deleteTrash();
};


