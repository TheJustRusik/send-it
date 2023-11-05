cmake_minimum_required(VERSION 3.5)
set(CMAKE_PREFIX_PATH "D:/Qt/6.5.1/mingw_64")
project(send-it VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)



set(PROJECT_SOURCES
        res/mainwindow.ui

        src/main.cpp

        inc/mainwindow.h
        src/mainwindow.cpp
        inc/devicelist.h
        src/devicelist.cpp
        inc/pelengator.h
        src/pelengator.cpp
        inc/filemanager.h
        src/filemanager.cpp
        inc/tcpmanager.h
        src/tcpmanager.cpp
        inc/dialogs/dialogwidget.h
        src/dialogs/dialogwidget.cpp
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(send-it
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


    )
    set_property(TARGET send-it APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
                ${CMAKE_CURRENT_SOURCE_DIR}/android)
else()
    if(ANDROID)
        add_library(send-it SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(send-it
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(send-it PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(send-it PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS send-it
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(send-it)
endif()
