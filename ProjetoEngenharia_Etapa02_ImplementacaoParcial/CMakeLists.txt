cmake_minimum_required(VERSION 3.20)

project(
    SimuladorJanelaOperacional_ImplementacaoParcial
    VERSION 0.5
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
    simulador_parcial
    src/main.cpp
    src/Camada.cpp
    src/ParametrosSimulacao.cpp
    src/Poco.cpp
    src/ModeloPetrofisico.cpp
    src/ModeloGeopressoes.cpp
)

target_include_directories(
    simulador_parcial
    PRIVATE
    include
)
