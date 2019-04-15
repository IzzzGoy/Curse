#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    numbOfPlayers = 0;
    //this->setStyleSheet("background-color: black;");
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_newgameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    _server = new server();
    _client.StartClient("127.0.0.1");
 //   _client.CloseClient();
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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_connectButton2_clicked()
{
    QByteArray tmp = ui->lineEditAddress->text().toLocal8Bit();
    _client.StartClient(tmp.data());
    sleep(10);
    _client.CloseClient();
    exit(0);
}

void MainWindow::on_toGameButton_clicked()
{
    _server->DoServer(numbOfPlayers);
    _client.CloseClient();
    exit(0);
    //   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_plusButton_clicked()
{
    if(numbOfPlayers < 4)
    {
        numbOfPlayers++;
        ui->label_2->setText(QString("%1").arg(numbOfPlayers));
    }
}
///Уменьшаем количество игроков, если их больше 1
void MainWindow::on_minusButton_clicked()
{
    if(numbOfPlayers > 1)
    {
        numbOfPlayers--;
        ui->label_2->setText(QString("%1").arg(numbOfPlayers));
    }
}
