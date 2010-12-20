#include <QtCore/QCoreApplication>
#include <QString>
#include "world.h"
#include "map.h"
#include "settings.h"

#define MAX_MAP_WIDTH 16
#define MAX_MAP_HEIGHT 16

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Settings *settings = Settings::getInstance();
    QString central_server_host = settings->central_server_host;
    int central_server_port = settings->central_server_port;
    QString host = settings->host;
    int port = settings->port;


    /*Since it's flexible, we need to check if the user has set valid map parameters
      otherwise we won't start the server application:*/


    if (settings->width > MAX_MAP_WIDTH || settings->width < 5 ||
       settings->height > MAX_MAP_HEIGHT || settings->height < 5)
    {
        qDebug("ERROR: width and height parameters should be between 5 and 16.");
        return 0;
    }

    if (settings->density > 10 | settings->density < 1)
    {
        qDebug("ERROR: density parameter should be between 0 and 10.");
        return 0;
    }

    if (settings->winterval < 1 || (settings->winterval > settings->width - 1 &&
        settings->winterval > settings->height - 1))
    {
        qDebug("ERROR: winterval parameter should be between 1 and the largest dimension - 1.");
        return 0;
    }

    if ( settings->ini_winterval < 2 ||
        (settings->ini_winterval >= (settings->width / 2)) &&
        (settings->ini_winterval >= (settings->height / 2)))
    {
        qDebug("ERROR: ini_winterval parameter should be more than 2 and less than the half of the largest dimension.");
        return 0;
    }

    if ( settings->finalx_winterval > (settings->width - 2) ||
         settings->finaly_winterval > (settings->height - 2) ||
         settings->finalx_winterval < settings->ini_winterval ||
         settings->finaly_winterval < settings->ini_winterval)
    {
        qDebug("ERROR: finalx_winterval and finaly_winterval parameters should be more than the ini_winterval parameter and less than the respective dimension.");
        return 0;
    }

    /*End of map parameters check.*/

    World world(QHostAddress(host), port);
    world.start(QHostAddress(central_server_host), central_server_port);

    return a.exec();
}
