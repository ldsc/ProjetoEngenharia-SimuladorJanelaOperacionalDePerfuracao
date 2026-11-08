cmake_minimum_required(VERSION 3.20)

project(
    SimuladorJanelaOperacional
    VERSION 1.0
    LANGUAGES CXX
)


# ==========================================================
# C++17
# ==========================================================

set(
    CMAKE_CXX_STANDARD
    17
)

set(
    CMAKE_CXX_STANDARD_REQUIRED
    ON
)


# ==========================================================
# QT
# ==========================================================

set(
    CMAKE_AUTOMOC
    ON
)


find_package(
    Qt6
    REQUIRED
    COMPONENTS Widgets
)


# ==========================================================
# NÚCLEO DO SIMULADOR
# ==========================================================

set(
    CORE_SOURCES

    src/Camada.cpp

    src/ParametrosSimulacao.cpp

    src/Poco.cpp

    src/ModeloPetrofisico.cpp

    src/ModeloGeopressoes.cpp

    src/ModeloFratura.cpp

    src/JanelaOperacional.cpp

    src/CalculadoraECD.cpp

    src/Resultados.cpp

    src/SimuladorJanelaOperacional.cpp
)


# ==========================================================
# EXECUTÁVEL CLI
# ==========================================================

add_executable(
    simulador_cli

    src/main.cpp

    ${CORE_SOURCES}
)


target_include_directories(
    simulador_cli

    PRIVATE

    include
)


# ==========================================================
# EXECUTÁVEL COM INTERFACE QT
# ==========================================================

add_executable(
    simulador_gui

    WIN32

    src/main_gui.cpp

    gui/MainWindow.cpp

    gui/MainWindow.h

    ${CORE_SOURCES}
)


target_include_directories(
    simulador_gui

    PRIVATE

    include

    gui
)


target_link_libraries(
    simulador_gui

    PRIVATE

    Qt6::Widgets
)