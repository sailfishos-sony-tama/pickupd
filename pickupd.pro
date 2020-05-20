TARGET = pickupd

QT -= gui
QT += network dbus

CONFIG += link_pkgconfig
PKGCONFIG += sensord-qt5

target.path = /usr/bin/

systemduser.files = $${TARGET}.service
systemduser.path = /etc/systemd/user/

INSTALLS += target systemduser

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

SOURCES += \
    src/$${TARGET}.cpp \
    src/sensorreader.cpp

OTHER_FILES += \
    rpm/$${TARGET}.spec \
    $${TARGET}.service

HEADERS += \
    src/sensorreader.h

