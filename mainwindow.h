#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtDebug>
#include <QtNetwork/QtNetwork>
#include <QThread>
#include <QCloseEvent>



namespace Ui {
class MainWindow;

}

class Thread : public QThread
{
    Q_OBJECT

    public:
        void run();
    signals:
        void resultReady(const QString &s);
    private:
        QTcpSocket *socket;
};



class MainWindow : public QMainWindow
{
    Q_OBJECT
    Thread *thread;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void on_pushButton_clicked();
        void on_closeButton_clicked();
        void on_textBrowser_windowIconTextChanged(const QString &iconText);

    private:
        Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
