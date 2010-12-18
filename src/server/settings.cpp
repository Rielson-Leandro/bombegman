#include "settings.h"

Settings *Settings::instance = NULL;

Settings::Settings() : QSettings("settings.ini", QSettings::IniFormat)
{
    this->central_server_host = value("network_parameters/central_server_host",
                                      "bomber.lccv.ufal.br").toString();
    this->central_server_port = value("network_parameters/central_server_port",
                                      50000).toInt();
    this->host = value("network_parameters/host", "0.0.0.0").toString();
    this->port = value("network_parameters/port",8799).toInt();

    this->density = value("map_generation/density", 8).toInt();
    this->winterval = value("map_generation/winterval", 2).toInt();
    this->ini_winterval = value("map_generation/ini_winterval", 2).toInt();
    this->final_winterval = value("map_generation/final_winterval", 12).toInt();
}

Settings *Settings::getInstance()
{
    if(!instance){
        instance = new Settings();
    }
    return instance;
}
