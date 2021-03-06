#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>
#include <client.h>
#include <pthread.h>
#include <QTimer>
#include <QKeyEvent>
#include <unistd.h>
#include <QGraphicsScene>
#include <QPixmap>
#include "table.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int numbOfPlayers;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static void* serverservis(void* arg);

private slots:

    void on_newgameButton_clicked();

    void on_exitButton_clicked();

    void on_connectButton_clicked();

    void on_goToMenuButton_clicked();

    void on_connectButton2_clicked();

    void on_toGameButton_clicked();

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void showpick();

protected:
    void keyPressEvent(QKeyEvent* e);

private:
    QTimer* timer;

    server* _server;
    client _client;
    Ui::MainWindow *ui;
    bool state = false;
    pthread_t tmp;
    QGraphicsScene* scene;
    Table table;


    void showresults();

    struct serverinfo
    {
        bool* state;
        server* _server;
        int numb;
        serverinfo(int numbOf,server* serv,bool* state)
        {
            this->state = state;
            numb = numbOf;
            _server = serv;
        }
    };
    serverinfo* serv;
};

#endif // MAINWINDOW_H
