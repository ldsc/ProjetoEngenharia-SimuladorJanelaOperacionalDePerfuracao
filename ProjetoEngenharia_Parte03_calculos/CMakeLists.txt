cmake_minimum_required(VERSION 3.20)

project(ProjetoEngenharia_Parte03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    simulador_parte03
    src/main.cpp
    src/Camada.cpp
    src/ParametrosSimulacao.cpp
    src/Poco.cpp
    src/ModeloPetrofisico.cpp
    src/ModeloGeopressoes.cpp
    src/ModeloFratura.cpp
    src/JanelaOperacional.cpp
    src/CalculadoraECD.cpp
)

target_include_directories(simulador_parte03 PRIVATE include)
