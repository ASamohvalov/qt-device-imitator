cmake_minimum_required(VERSION 3.14)

project(device-imitators LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core SerialBus)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialBus)

add_executable(device-imitators
    src/main.cpp
    src/temperature_meter.h src/temperature_meter.cpp

    src/config.h
    src/device_imitator.h src/device_imitator.cpp
    src/devices/trm210_server.h src/devices/trm210_server.cpp
    src/devices/trm10_server.h src/devices/trm10_server.cpp
    src/devices/b5_100_server.h src/devices/b5_100_server.cpp
    src/devices/keysight_33510b_server.h src/devices/keysight_33510b_server.cpp
)
target_link_libraries(device-imitators
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialBus
)

include(GNUInstallDirs)
install(TARGETS device-imitators
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
