TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    src/rf_meter_hal.c \
    src/rf_meter_hw.c

INCLUDEPATH += \
        include/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    include/rf_meter_hal.h \
    include/rf_meter_hw.h

