#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;
class QTextEdit;
class QTcpSocket;
class QLabel;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void onConnectionRequest();
    void onReconnectionRequest();
    void onDisconnectionRequest();
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QPlainTextEdit *textEdit;
    QTextEdit *textBrowser;
    QTcpSocket *socket;
    QLabel *status;

    QString host;
    quint16 port;
};

#endif // MAINWINDOW_H
