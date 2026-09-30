# Correspondência entre projeto e C++

| Representação UML | Expressão nesta etapa | Estado |
|---|---|---|
| Classes | Dez cabeçalhos e dez implementações | Estrutura compilável |
| Composição | Simulador contém Poco, ParametrosSimulacao e Resultados; Poco contém vetor de Camada; Resultados contém vetor de JanelaOperacional | Preservada do anexo |
| Associação | Modelos armazenam ponteiro const para ParametrosSimulacao | Parâmetros devem viver mais que os modelos |
| Casos de uso | Métodos carregarDadosCSV, calcularPetrofisica, calcularGeopressoes, calcularFratura, determinarJanelas, avaliarECD e exportarResultados | Contratos presentes; execução pendente |
| Atividades e sequência | executarSimulacao preservado do anexo | Fluxo presente; operações físicas pendentes |
| Comunicação | Chamadas do simulador aos modelos e objetos | Representadas pela sequência e pelas interfaces |
| Estado da ECD | validarParametros, calcularECD e avaliarJanela | Máquina de estados explícita ainda pendente; sem alegação de equivalência ao UML |
| Componentes | Biblioteca estrutura e executável etapa1, configurados no CMake | Organização local inicial |
| Implantação | Compilação e execução local no VS Code | Servidor, rede e armazenamento externos ainda não implementados |

## Classes da referência anexada

- `CalculadoraECD`: `include/CalculadoraECD.h` e `src/CalculadoraECD.cpp`.
- `Camada`: `include/Camada.h` e `src/Camada.cpp`.
- `JanelaOperacional`: `include/JanelaOperacional.h` e `src/JanelaOperacional.cpp`.
- `ModeloFratura`: `include/ModeloFratura.h` e `src/ModeloFratura.cpp`.
- `ModeloGeopressoes`: `include/ModeloGeopressoes.h` e `src/ModeloGeopressoes.cpp`.
- `ModeloPetrofisico`: `include/ModeloPetrofisico.h` e `src/ModeloPetrofisico.cpp`.
- `ParametrosSimulacao`: `include/ParametrosSimulacao.h` e `src/ParametrosSimulacao.cpp`.
- `Poco`: `include/Poco.h` e `src/Poco.cpp`.
- `Resultados`: `include/Resultados.h` e `src/Resultados.cpp`.
- `SimuladorJanelaOperacional`: `include/SimuladorJanelaOperacional.h` e `src/SimuladorJanelaOperacional.cpp`.
