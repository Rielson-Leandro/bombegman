#include "settings.h"

Settings *Settings::instance = NULL;

Settings::Settings() :
    QSettings("settings.ini", QSettings::IniFormat),
    central_server_host(value("network_parameters/central_server_host",
                              "127.0.0.1").toString()),
    central_server_port(value("network_parameters/central_server_port",
                              50000).toInt()),
    host(value("network_parameters/host", "0.0.0.0").toString()),
    port(value("network_parameters/port",8799).toInt()),
    width(value("map_generation/width", 15).toInt()),
    height(value("map_generation/height", 15).toInt()),
    density(value("map_generation/density", 8).toInt()),
    winterval(value("map_generation/winterval", 2).toInt()),
    ini_winterval(value("map_generation/ini_winterval", 2).toInt()),
    finalx_winterval(value("map_generation/finalx_winterval", 12).toInt()),
    finaly_winterval(value("map_generation/finaly_winterval", 12).toInt())
{
}

Settings *Settings::getInstance()
{
    if(!instance){
        instance = new Settings();
    }
    return instance;
}
