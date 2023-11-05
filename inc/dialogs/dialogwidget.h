#pragma once

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    ConnectDialog(const QString &username, QWidget *parent);
};
