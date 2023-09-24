#pragma once

#include <QtNetwork>
#include <QtCore>
#include <QObject>
#include <QListWidget>

enum state{
    sending,
    receiving,
    nothing
};

class TCPManager : public QObject{
    Q_OBJECT
private:
    state current_state = nothing;
    QTcpSocket* socket;
    QTcpServer* server;
    
public:

private slots:

};