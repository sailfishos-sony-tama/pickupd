#include <QtCore/QCoreApplication>
#include <QDebug>

#include "sensorreader.h"

int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);

  SensorReader sr;

  return app.exec();
}
