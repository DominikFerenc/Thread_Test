#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QThread>


#define MSG_ERR "Watek nie działa"
#define MSG_OK "Wątek działa"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    if(thread == NULL){
        thread = new Thread;
        thread->start();
        connect(thread, &Thread::resultReady, this, &MainWindow::on_textBrowser_windowIconTextChanged);
    }
}
void MainWindow::on_textBrowser_windowIconTextChanged(const QString &iconText)
{
    ui->textBrowser->append(iconText);
}
void Thread::run()
{
    QTcpSocket * socket = new QTcpSocket();
    socket->connectToHost("www.google.pl", 80);
    QString request = "GET / \r\n";


    QByteArray b;
    b.append(request);
    socket->write(b);



    while (socket->waitForReadyRead())
    {
       QByteArray bb = socket->readAll();
       QString string(bb);
       emit resultReady(string);
    }



}



void MainWindow::on_closeButton_clicked()
{
    this->close();
}
