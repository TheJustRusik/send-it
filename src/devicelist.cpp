#include "../inc/devicelist.h"

#include <QtMath>
#include <QTimer>

void DeviceList::addItem(QString name, QHostAddress address){
    QList<QListWidgetItem *> objs = list->findItems("Name: " + name + "\nAddress: " + address.toString(), Qt::MatchExactly);
    if(!objs.isEmpty()){
        if (objs.size() > 1) qDebug() << "WTF?";
        devices[objs[0]] = QTime::currentTime();

    }else{
        QListWidgetItem* obj = new QListWidgetItem("Name: " + name + "\nAddress: " + address.toString());
        devices.insert(obj, QTime::currentTime());
        list->addItem(obj);
    }
}

void DeviceList::deleteTrash(){
    QHashIterator<QListWidgetItem*, QTime> it(devices);
    QTime currentTime = QTime::currentTime();
    while (it.hasNext()) {
        it.next();
        if(qAbs(currentTime.secsTo(it.value())) > 3){
            list->takeItem(list->row(it.key()));
            devices.remove(it.key());
        }
    }
}
