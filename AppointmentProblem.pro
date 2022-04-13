QT       += core gui 3dcore 3dextras 3dlogic 3dinput 3drender

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Axis.cpp \
    AxisTip.cpp \
    Cube.cpp \
    Decision.cpp \
    GeometricProbabilityModel.cpp \
    Graph2d.cpp \
    Graph3d.cpp \
    Line.cpp \
    Polygon.cpp \
    Scene.cpp \
    SegmentPoint.cpp \
    main.cpp \
    mainwindow.cpp \
    task.cpp

HEADERS += \
    Axis.h \
    AxisTip.h \
    Cube.h \
    Decision.h \
    GeometricProbabilityModel.h \
    Graph2d.h \
    Graph3d.h \
    IGraph.h \
    IRenderable.h \
    Line.h \
    Polygon.h \
    Scene.h \
    SegmentPoint.h \
    mainwindow.h \
    task.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
