#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QHBoxLayout;

class ConnectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectDialog(QWidget *parent = 0);

    QString hostAddress() const;
    int port() const;

private slots:
    void onConnectButtonClicked();

private:
    QLineEdit *m_hostLineEdit;
    QLineEdit *m_portLineEdit;
};

#endif // CONNECTDIALOG_H
