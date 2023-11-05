#pragma once

#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QListWidget>
#include <QDialog>

enum State{
    Sending,
    Receiving,
    Nothing
};



class TCPManager : public QObject{
    Q_OBJECT
private:
    State current_state = Nothing;
    QTcpSocket* socket;
    QTcpServer* server;
    
public:
    TCPManager(QObject* parent);
private slots:

};