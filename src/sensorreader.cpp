#include "sensorreader.h"

#include <QTimer>
#include <QDebug>

SensorReader::SensorReader(QObject *parent) : QObject(parent)
{
  SensorManagerInterface& sm = SensorManagerInterface::instance();
  sm.loadPlugin("tapsensor");
  sm.registerSensorInterface<TapSensorChannelInterface>("tapsensor");

  sensor = TapSensorChannelInterface::interface("tapsensor");

  if (sensor == nullptr || !sensor->isValid())
    {
      qCritical() << "Unable to get sensor session: %s\n" << qPrintable(sm.errorString());
      QCoreApplication::quit();
      return;
    }

  sensor->setTapType(TapSensorChannelInterface::SingleDouble);
  sensor->start();
  sensor->setStandbyOverride(true);

  connect(sensor, SIGNAL(dataAvailable(const Tap&)), this, SLOT(dataAvailable(const Tap&)));

  mce = new QDBusInterface("com.nokia.mce", "/com/nokia/mce/request", "com.nokia.mce.request", QDBusConnection::systemBus(), this);
  if (!mce->isValid())
    {
      qCritical() << "Cannot connect to MCE DBus: Request";
      QCoreApplication::quit();
      return;
    }

  QDBusConnection::systemBus().connect("com.nokia.mce", "/com/nokia/mce/signal", "com.nokia.mce.signal",
                                       "display_status_ind", this, SLOT(displayChanged(QString)));
}

void SensorReader::dataAvailable(const Tap &data)
{
  qDebug() << "Received pickup sensor activity";
  mce->call("req_display_state_on");
}

void SensorReader::displayChanged(QString state)
{
  qDebug() << "New display state: " << state;
  if (state == "on") sensor->stop();
  else if (state == "off") sensor->start();
}

//void SensorReader::restartSensor()
//{
//  qDebug() << "Restarting sensor";
//  sensor->stop();
//  sensor->start();
//  qDebug() << "Sensor restarted";
//}
