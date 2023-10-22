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
    ui->name_line_edit->setText(hostName);
    qDebug() << "My name is: " << hostName;
    
    pelengator = new Pelengator(this, hostName, ui->devices_list);
    connect(ui->devices_list, &QListWidget::itemPressed, this, &MainWindow::devicePicked);

    qDebug() << "File hash: " << FileManager::calculate_file_hash("C://Users//7thej//Desktop//1.png");
}

void MainWindow::connectBtnRls(){
    qDebug() << "Connect btn released!";
    ui->pages->setCurrentIndex(1);
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

}

