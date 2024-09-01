cmake_minimum_required(VERSION 3.5)

project(smart_calc VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools PrintSupport)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra")

set(PROJECT_SOURCES
        back/s21_calc.h
        back/s21_calc.cc
        back/s21_functions.cc
        back/s21_parser.cc
        back/s21_polish.cc

        front/s21_calculator.cc
        front/s21_calculator.h
        front/s21_calculator.ui
        front/qcustomplot.cc
        front/qcustomplot.h

        s21_controller.h
        s21_controller.cc

        main.cc

        pictures.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smart_calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        misc/icon.ico
    )
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}
    misc/icon.ico
    )
endif()

target_include_directories(smart_calc PRIVATE front)
target_include_directories(smart_calc PRIVATE back)

target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)


set_target_properties(smart_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_ICON_FILE ../Resources/icon.ico
    RESOURCE misc/icon.ico
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smart_calc)
endif()
