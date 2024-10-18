TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        red_nacional.cpp
INCLUDEPATH+=C:/Users/USUARIO/Downloads/jsoncpp-1.9.6/jsoncpp-1.9.6/include
LIBS += -LC:/Users/USUARIO/Downloads/jsoncpp-1.9.6/jsoncpp-1.9.6/lib -ljsoncpp

HEADERS += \
    red_nacional.h
