#ifndef DEVICELIST_H
#define DEVICELIST_H
#include <QString>
#include <QTimer>
#include <QTime>
#include <QHash>
#include <QListWidget>
#include <QHostAddress>
#include <QMainWindow>
#include <QtNetwork>
#include <QtCore>

class DeviceList{
private:
    QHash<QListWidgetItem*, QTime> devices;
public:
    QString myName;
    QListWidget* list;
    void addItem(QString name, QHostAddress address);
    void deleteTrash();
};

#endif // DEVICELIST_H
