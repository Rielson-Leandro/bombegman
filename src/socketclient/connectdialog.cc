#include "connectdialog.h"
#include <QIntValidator>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

static const QIntValidator validator(0, 65535, NULL);

ConnectDialog::ConnectDialog(QString host, quint16 port, QWidget *parent) :
    QDialog(parent),
    hostLineEdit(new QLineEdit),
    portLineEdit(new QLineEdit)
{
    hostLineEdit->setPlaceholderText("Host address");
    portLineEdit->setPlaceholderText("Port address");
    hostLineEdit->setText(host);
    if (port)
        portLineEdit->setText(QString::number(port));

    QPushButton *connectButton = new QPushButton("Connect");

    connect(connectButton, SIGNAL(clicked()), this, SLOT(onConnectRequest()));

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(hostLineEdit);
    l->addWidget(portLineEdit);
    l->addWidget(connectButton);

    setLayout(l);
}

void ConnectDialog::onConnectRequest()
{
    if (hostLineEdit->text().isEmpty()) {
        QMessageBox::warning(this,
                             "Host address required",
                             "Please enter the host address");
        return;
    }

    if (portLineEdit->text().isEmpty()) {
        QMessageBox::warning(this,
                             "Port address required",
                             "Please enter the port address");
        return;
    }

    accept();
}

QString ConnectDialog::hostAddress() const
{
    return hostLineEdit->text();
}

quint16 ConnectDialog::portAddress() const
{
    return portLineEdit->text().toInt();
}
