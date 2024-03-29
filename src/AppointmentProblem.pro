QT       += core gui 3dcore 3dextras 3dlogic 3dinput 3drender positioning webenginewidgets

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
    Scene.cpp \
    SegmentPoint.cpp \
    ColoredPolygon.cpp \
    UncoloredPolygon.cpp \
    main.cpp \
    mainwindow.cpp \
    task.cpp \
    webView/webView.cpp

HEADERS += \
    Axis.h \
    AxisTip.h \
    Cube.h \
    Decision.h \
    GeometricProbabilityModel.h \
    Graph2d.h \
    Graph3d.h \
    IPolygon.h \
    IGraph.h \
    IRenderable.h \
    ColoredPolygon.h \
    UncoloredPolygon.h \
    Line.h \
    Scene.h \
    SegmentPoint.h \
    common/constants.h \
    common/json.h \
    common/mathematicFuncs.h \
    "include/earcut.h" \
    mainwindow.h \
    task.h \
    webView/webView.h

FORMS += \
    mainwindow.ui \
    webView/webView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
