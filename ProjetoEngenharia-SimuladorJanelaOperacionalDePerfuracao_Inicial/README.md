# Simulador de Janela Operacional de Perfuração

Estrutura inicial em C++ orientada a objetos.

## Compilar com g++

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o simulador
```

No Windows/MinGW:

```powershell
g++ -std=c++17 -Iinclude src/*.cpp -o simulador.exe
.\simulador.exe
```

## Compilar com CMake

```bash
cmake -S . -B build
cmake --build build
```

A primeira versão carrega `data/dados_poco.csv` e valida a estrutura do poço.
Os modelos de geopressões e fratura permanecem intencionalmente como etapas futuras para mostrar a evolução semanal do projeto.
