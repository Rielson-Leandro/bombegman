#include "settings.h"

Settings *Settings::instance = NULL;

Settings::Settings() : QSettings("settings.ini",QSettings::IniFormat)
{
    this->central_server_host = this->value("central_server_host",
                                            "bomber.lccv.ufal.br").toString();
    this->central_server_port = this->value("central_server_port",
                                            50000).toInt();
    this->host = this->value("host", "0.0.0.0").toString();
    this->port = this->value("port",8799).toInt();

    this->density = this->value("density", 8).toInt();
    this->winterval = this->value("winterval", 2).toInt();
    this->ini_winterval = this->value("ini_winterval", 2).toInt();
    this->final_winterval = this->value("final_winterval", 12).toInt();
}

Settings *Settings::getInstance()
{
    if(!instance){
        instance = new Settings();
    }
    return instance;
}
