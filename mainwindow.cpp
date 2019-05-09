#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    numbOfPlayers = 0;
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setStyleSheet("background-color: black;");
}
MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete _server;
    delete serv;
    delete ui;
}

void* MainWindow::serverservis(void* arg)
{
    serverinfo* info = static_cast<serverinfo*>(arg);
//    cout<<"Thread server adress: "<<info->_server<<endl;
//    cout<<"Thread info address :"<<info<<endl;
    info->_server->DoServer(info->numb);
    *info->state = true;
    pthread_exit(0);
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
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_3->setText(QString("%1").arg(0));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(showpick()));
    timer->start(33);

//    sleep(10);
//    _client.CloseClient();
//    exit(0);
}

void MainWindow::on_toGameButton_clicked()
{
    serv = new serverinfo(numbOfPlayers,_server,&state);
//    cout<<"Server address: "<<_server<<endl;
//    cout<<"Info server address:: "<<serv->_server<<endl;
//    cout<<"Info address: "<<serv<<endl;
//    cout<<"Scene address: "<<scene<<endl;
    pthread_create(&tmp,0,serverservis,static_cast<void*>(serv));
//    _server->DoServer(numbOfPlayers);
//    _client.CloseClient();
//    exit(0);
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_3->setText(QString("%1").arg(0));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(showpick()));
    timer->start(30);
//    pthread_join(tmp,NULL);
//    _client.CloseClient();
//    exit(0);
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    char key = e->key();
    //cout<<key<<"////////////"<<key<<endl;
    if(key == 'W'||key == 'w')
    {
        _client.setdirection('u');
    }
    else if(key == 'S'||key == 's')
    {
        _client.setdirection('d');
    }
    else if(key == 'A'||key == 'a')
    {
        _client.setdirection('l');
    }
    else if(key == 'D'||key == 'd')
    {
        _client.setdirection('r');
    }
}

void MainWindow::showresults()
{
    /*код отображения результатов*/
    sleep(3);
}

void MainWindow::showpick()
{
    bool t = _client.acceptcoord();
    if(!state)
    {

        table.Drow(_client.coordinats.grid,_client.coordinats.X,_client.coordinats.Y,scene);
    }
    else
    {
        showresults();
        pthread_join(tmp,NULL);
        _client.CloseClient();
        exit(0);
    }
}
