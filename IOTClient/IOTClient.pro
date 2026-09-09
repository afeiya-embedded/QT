QT += widgets
QT += serialport
QT += network mqtt

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canopen.cpp \
    main.cpp \
    modbus.cpp \
    mqtt.cpp

HEADERS += \
    canopen.h \
    modbus.h \
    mqtt.h

FORMS += \
    canopen.ui \
    modbus.ui \
    mqtt.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

RC_ICONS = images/logo.ico

msvc {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS   += /utf-8
}