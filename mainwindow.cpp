#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //this->setStyleSheet("background-color: black;");
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_newgameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    server _server = server();
    _client.StartClient("127.0.0.1");
    _server.DoServer(1);
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::on_connectButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_goToMenuButton_clicked()
{
    //char tmp[20];

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_connectButton2_clicked()
{
    QByteArray tmp = ui->lineEditAddress->text().toLocal8Bit();
    _client.StartClient(tmp.data());
}
