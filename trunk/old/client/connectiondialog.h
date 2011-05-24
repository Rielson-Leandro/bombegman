#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QWidget>
#include <QHostAddress>

class QTcpSocket;
class QListWidget;

class ConnectionDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionDialog(const QHostAddress &add, quint16 port,
                              QWidget *parent = 0);
    ~ConnectionDialog();

signals:
    void connectionRequested(QHostAddress address, quint16 port);

private slots:
    void onConnectButtonClicked();
    void onRefreshButtonCLicked();
    void onConnected();
    void onReadyRead();

private:
    QListWidget *list;
    QTcpSocket *socket;
    QByteArray buffer;
    QHostAddress host;
    quint16 port;
};

#endif // CONNECTDIALOG_H
