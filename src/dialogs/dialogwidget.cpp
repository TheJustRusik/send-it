#include "../../inc/dialogs/dialogwidget.h"

ConnectDialog::ConnectDialog(const QString &username, QWidget *parent = nullptr) : QDialog(parent){
    setWindowTitle("Запрос на подключение");

    QLabel *label = new QLabel("К вам хочет подключиться пользователь: " + username, this);

    QPushButton *connectButton = new QPushButton("Подключиться", this);
    QPushButton *disconnectButton = new QPushButton("Неподключиться", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(connectButton);
    layout->addWidget(disconnectButton);

    connect(connectButton, &QPushButton::clicked, this, &ConnectDialog::accept);
    connect(disconnectButton, &QPushButton::clicked, this, &ConnectDialog::reject);
}
