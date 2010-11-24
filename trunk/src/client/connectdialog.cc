#include "connectdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QIntValidator>

static const QIntValidator validator(0, 65535, NULL);

ConnectDialog::ConnectDialog(QWidget *parent) :
        QDialog(parent),
        m_hostLineEdit(new QLineEdit),
        m_portLineEdit(new QLineEdit)
{
    m_hostLineEdit->setPlaceholderText(QObject::tr("Host address"));
    m_hostLineEdit->setText("localhost");
    m_portLineEdit->setPlaceholderText(QObject::tr("Port address"));
    m_portLineEdit->setValidator(&validator);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonGroupLayout = new QHBoxLayout;

    QPushButton *buttons[2] = {new QPushButton(QObject::tr("Connect")),
                               new QPushButton(QObject::tr("Cancel"))};

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(reject()));

    buttonGroupLayout->addWidget(buttons[0]);
    buttonGroupLayout->addWidget(buttons[1]);

    mainLayout->addWidget(m_hostLineEdit);
    mainLayout->addWidget(m_portLineEdit);
    mainLayout->addLayout(buttonGroupLayout);

    setLayout(mainLayout);
}

void ConnectDialog::onConnectButtonClicked()
{
    if (m_hostLineEdit->text().isEmpty()) {
        QMessageBox::warning(this,
                             QObject::tr("Host address required"),
                             QObject::tr("Please enter the host address"));
        return;
    }

    if (m_portLineEdit->text().isEmpty()) {
        QMessageBox::warning(this,
                             QObject::tr("Port address required"),
                             QObject::tr("Please enter the port address"));
        return;
    }

    QDialog::accept();
}

QString ConnectDialog::hostAddress() const
{
    return m_hostLineEdit->text();
}

int ConnectDialog::port() const
{
    return m_portLineEdit->text().toInt();
}
