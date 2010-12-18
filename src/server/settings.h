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
    QString central_server_host;
    int central_server_port;
    QString host;
    int port;

    int density;
    int winterval;
    int ini_winterval;
    int final_winterval;
};

#endif // SETTINGS_H
