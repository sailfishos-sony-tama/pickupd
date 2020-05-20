#ifndef SENSORREADER_H
#define SENSORREADER_H

#include <QObject>
#include <QDBusInterface>
#include <QString>

#include <sensord-qt5/sensormanagerinterface.h>
#include <sensord-qt5/tapsensor_i.h>

class SensorReader : public QObject
{
  Q_OBJECT
public:
  explicit SensorReader(QObject *parent = nullptr);

signals:

public slots:
  void dataAvailable(const Tap& data);
  void displayChanged(QString state);

//private:
//  void restartSensor();

private:
  TapSensorChannelInterface* sensor;
  QDBusInterface *mce;
};

#endif // SENSORREADER_H
