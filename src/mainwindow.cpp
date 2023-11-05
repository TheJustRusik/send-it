#include "../inc/mainwindow.h"
#include "../res/ui_mainwindow.h"
#include "../inc/filemanager.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);

    //get and show our name
    hostName = QHostInfo::localHostName();
    ui->name_line_edit->setText(hostName);
    qDebug() << "My name is: " << hostName;
    
    pelengator = new Pelengator(this, hostName, ui->devices_list);
    connect(ui->devices_list, &QListWidget::itemPressed, this, &MainWindow::devicePicked);
}

void MainWindow::connectBtnRls(){
    qDebug() << "Connect btn released!";
    ConnectDialog a("TEST", nullptr);
    if (a.exec() == QDialog::Accepted) {
        qDebug() << "Accepted";
        ui->pages->setCurrentIndex(1);
    } else {
        qDebug() << "Rejected";
    }
    

}

void MainWindow::devicePicked(QListWidgetItem* device){
    qDebug() << "device was selected" << device->text() << " address: " << pelengator->get_address(device);
}


void MainWindow::changeNamePressed(){
    if (ui->name_line_edit->isReadOnly()){
        ui->name_line_edit->setReadOnly(false);
        ui->change_name_button->setText("Готово!");
    }else{
        ui->name_line_edit->setReadOnly(true);
        ui->change_name_button->setText("Изменить");
        ui->name_line_edit->setFocus();
        hostName = ui->name_line_edit->text();
    }
}

void MainWindow::toMain(){
    qDebug() << "Cancel button released!";
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_file_choose_button_released()
{
    const auto choosen_files = QFileDialog::getOpenFileNames(this);
    for (auto i : choosen_files){
        qDebug() << "Hash:" << FileManager::calculate_file_hash(i) << "Path:" << i;
    }
}

