cmake_minimum_required(VERSION 3.16)
project(DiagramasCppEtapa1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(estrutura
    src/CalculadoraECD.cpp
    src/Camada.cpp
    src/JanelaOperacional.cpp
    src/ModeloFratura.cpp
    src/ModeloGeopressoes.cpp
    src/ModeloPetrofisico.cpp
    src/ParametrosSimulacao.cpp
    src/Poco.cpp
    src/Resultados.cpp
    src/SimuladorJanelaOperacional.cpp
)
target_include_directories(estrutura PUBLIC include)
add_executable(etapa1 src/main.cpp)
target_link_libraries(etapa1 PRIVATE estrutura)
