# Simulador de Janela Operacional de Perfuração

## Implementação parcial — etapa intermediária

Este diretório representa um **snapshot parcial e compilável da implementação** do projeto.
Os diagramas UML e a especificação do sistema já definem a arquitetura completa, enquanto
esta etapa concentra a primeira metade do núcleo em C++17.

### Implementado nesta etapa

- `Camada`
- `ParametrosSimulacao`
- `Poco`
- `ModeloPetrofisico`
- `ModeloGeopressoes`
- leitura dos CSVs de dados e parâmetros no executável de demonstração
- validação básica dos dados do poço
- cálculo de porosidade pelo método de Wyllie
- cálculo de densidade bulk
- integração da tensão de sobrecarga
- tendência normal do perfil sônico
- pressão de poros pelo método de Eaton
- gradiente de pressão de poros

### Próximas etapas

- `ModeloFratura`
- `JanelaOperacional`
- `CalculadoraECD`
- `Resultados`
- `SimuladorJanelaOperacional`
- exportação final
- integração dos gráficos
- interface gráfica Qt

## Compilação com CMake

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\simulador_parcial.exe
```

## Compilação direta com g++

```powershell
g++ -std=c++17 -Iinclude src\main.cpp src\Camada.cpp src\ParametrosSimulacao.cpp src\Poco.cpp src\ModeloPetrofisico.cpp src\ModeloGeopressoes.cpp -o simulador_parcial.exe
.\simulador_parcial.exe
```

> Observação: execute o programa a partir da raiz do projeto para que os arquivos da pasta `data/` sejam encontrados.
