cmake_minimum_required(VERSION 3.21)
project(AppointmentProblem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "D:/Programs/Qt/6.2.4/mingw_64")
else ()
    #todo разобраться с qt на линухе
    set(CMAKE_PREFIX_PATH "/home/vany/Qt/6.2.4/gcc_64/lib/cmake")
#    set(CMAKE_PREFIX_PATH "/home/vany/Qt/6.2.4/gcc_64/lib/cmake/Qt63DCore/Qt63DCoreConfig.cmake")

#    set(Qt6Core_DIR "/home/vany/Qt/6.2.4/gcc_64/lib/cmake/Qt6Core/")
#    set(Qt6_DIR "/home/vany/Qt/6.2.4/gcc_64/lib/cmake/Qt6/")
#    set(QT_MAKE_EXECUTABLE "/home/vany/Qt/6.2.4/gcc_64/bin/qmake")
endif ()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        3DCore
        3DLogic
        3DExtras
        3DInput
        3DRender
        REQUIRED)

add_executable(
        AppointmentProblem
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
        IGraph.h
        SegmentPoint.cpp SegmentPoint.h
        Axis.cpp Axis.h
        GeometricProbabilityModel.cpp GeometricProbabilityModel.h
        Graph2d.cpp Graph2d.h
        Polygon.cpp Polygon.h
        Line.cpp Line.h
        Scene.cpp Scene.h
        common/mathematicFuncs.h
        AxisTip.cpp AxisTip.h
        Graph3d.cpp Graph2d.h
        Decision.h Decision.cpp
        Cube.h Cube.cpp
)

target_link_libraries(AppointmentProblem
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::3DCore
        Qt::3DLogic
        Qt::3DExtras
        Qt::3DInput
        Qt::3DRender
        )

if (WIN32)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/renderers/openglrenderer.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/renderers/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/renderers/openglrenderer.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/renderers/")
    endif ()

    foreach (QT_LIB
            Core
            Gui
            Widgets
            3DCore
            3DLogic
            3DExtras
            3DInput
            3DRender
            Network
            Concurrent
            OpenGL
            )
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
