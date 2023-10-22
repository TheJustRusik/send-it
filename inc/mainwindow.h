#pragma once

#include <QMainWindow>
#include <QtNetwork>
#include <QtCore>
#include <QFileDialog>
#include "pelengator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Pelengator* pelengator;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QString hostName;
private slots:
    void changeNamePressed();
    void connectBtnRls();
    void devicePicked(QListWidgetItem* device);
    void toMain();
    void on_file_choose_button_released();
};

