#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>
#include <client.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_newgameButton_clicked();

    void on_exitButton_clicked();

    void on_connectButton_clicked();

    void on_goToMenuButton_clicked();

    void on_connectButton2_clicked();

    void on_toGameButton_clicked();

    void on_plusButton_clicked();

    void on_minusButton_clicked();

private:
    int numbOfPlayers;
    server* _server;
    client _client;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H