#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

class QLineEdit;

class ConnectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectDialog(QString host = QString(),
                           quint16 port = 0,
                           QWidget *parent = 0);

    QString hostAddress() const;
    quint16 portAddress() const;

private slots:
    void onConnectRequest();

private:
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
};

#endif // CONNECTDIALOG_H
