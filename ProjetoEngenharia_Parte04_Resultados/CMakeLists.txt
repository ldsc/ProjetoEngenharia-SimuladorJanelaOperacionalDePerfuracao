cmake_minimum_required(VERSION 3.20)

project(ProjetoEngenharia_Parte04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    simulador_parte04
    src/main.cpp
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

target_include_directories(simulador_parte04 PRIVATE include)
