#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT

private:
    Settings();
    static Settings *instance;

public:
    static Settings *getInstance();

    const QString central_server_host;
    const int central_server_port;
    const QString host;
    const int port;

    const int width;
    const int height;
    const int density;
    const int winterval;
    const int ini_winterval;
    const int finalx_winterval;
    const int finaly_winterval;
};

#endif // SETTINGS_H
