#include "../inc/devicelist.h"

#include <QtMath>
#include <QTimer>
#include <utility>

void DeviceList::addItem(const QString& name, const QHostAddress& address){
    auto objs = list->findItems("Name: " + name + "\nAddress: " + address.toString(), Qt::MatchExactly);
    if(!objs.isEmpty()){
        if (objs.size() > 1) qDebug() << "WTF?";
        devices[objs[0]] = TimeAndAddress{QTime::currentTime(), address};

    }else{
        auto* obj = new QListWidgetItem("Name: " + name + "\nAddress: " + address.toString());
        devices.insert(obj, TimeAndAddress{QTime::currentTime(), address});
        list->addItem(obj);
    }
}

void DeviceList::deleteTrash(){
    qDebug() << "Clearing";
    QHashIterator<QListWidgetItem*, TimeAndAddress> it(devices);
    auto currentTime = QTime::currentTime();
    while (it.hasNext()) {
        it.next();
        if(qAbs(currentTime.msecsTo(it.value().time)) > clear_delay.count()){
            list->takeItem(list->row(it.key()));
            devices.remove(it.key());
        }
    }
}

QHostAddress DeviceList::getAddress(QListWidgetItem *device) {
    return devices[device].address;
}

DeviceList::DeviceList(QObject* parent, QListWidget *list, QString name, chr::milliseconds clear_delay_ms) : QObject(parent), myName(std::move(name)), list(list), clear_delay(clear_delay_ms) {
    clear_timer = new QTimer(this);
    connect(clear_timer, &QTimer::timeout, this, &DeviceList::deleteTrash);
    qDebug() << clear_delay.count();
    clear_timer->start(clear_delay);

}

