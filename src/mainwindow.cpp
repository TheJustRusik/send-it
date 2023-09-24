#include "../inc/mainwindow.h"
#include "../res/ui_mainwindow.h"
#include "../inc/filemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //get and show our name
    hostName = QHostInfo::localHostName();
    ui->lineEdit->setText(hostName);
    qDebug() << "My name is: " << hostName;

    pelengator = new Pelengator(this, hostName, ui->listWidget);
    connect(ui->listWidget, &QListWidget::itemPressed, this, &MainWindow::devicePicked);

    qDebug() << "File hash: " << FileManager::calculate_file_hash("C://Users//7thej//Desktop//1.png");
}

void MainWindow::connectBtnRls(){
    qDebug() << "Connect btn released!";
}

void MainWindow::devicePicked(QListWidgetItem* device){
    qDebug() << "device was selected" << device->text() << " address: " << pelengator->get_address(device);
}


void MainWindow::changeNamePressed(){
    if (ui->lineEdit->isReadOnly()){
        ui->lineEdit->setReadOnly(false);
        ui->chngNmButton->setText("Готово!");
    }else{
        ui->lineEdit->setReadOnly(true);
        ui->chngNmButton->setText("Изменить");
        ui->lineEdit->setFocus();
        hostName = ui->lineEdit->text();
    }
}

