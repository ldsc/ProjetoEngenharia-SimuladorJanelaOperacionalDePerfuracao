# Simulador de Janela Operacional de Perfuração

Projeto desenvolvido em **C++17** com programação orientada a objetos para simulação e análise da **Janela Operacional de Perfuração**.

O software permite importar dados de poço, configurar parâmetros petrofísicos e geomecânicos, calcular geopressões e gradiente de fratura, determinar a janela operacional, avaliar a **ECD (Equivalent Circulating Density)**, visualizar resultados e gerar gráficos técnicos.

---

## Funcionalidades implementadas

O sistema contempla atualmente:

- leitura dos dados do poço por arquivo CSV;
- classificação dos tipos de camada;
- configuração dos parâmetros da simulação por CSV ou pela interface;
- cálculo da porosidade pelo modelo de Wyllie;
- cálculo da densidade bulk;
- cálculo da tensão de sobrecarga;
- cálculo da tendência normal de compactação;
- cálculo da pressão de poros pelo método de Eaton;
- cálculo do gradiente de poros;
- cálculo da tensão horizontal mínima;
- cálculo do gradiente de fratura;
- determinação da janela operacional de perfuração;
- cálculo da ECD;
- classificação da ECD em relação à janela operacional;
- apresentação dos resultados em tabela;
- exportação dos resultados em arquivos CSV;
- geração de gráficos técnicos utilizando Gnuplot;
- visualização dos gráficos diretamente na interface Qt.

---

## Estrutura principal do projeto

```text
data/
    dados_poco.csv
    parametros_simulacao.csv

gui/
    MainWindow.cpp
    MainWindow.h

include/
    CalculadoraECD.h
    Camada.h
    JanelaOperacional.h
    ModeloFratura.h
    ModeloGeopressoes.h
    ModeloPetrofisico.h
    ParametrosSimulacao.h
    Poco.h
    Resultados.h
    SimuladorJanelaOperacional.h

src/
    CalculadoraECD.cpp
    Camada.cpp
    JanelaOperacional.cpp
    main.cpp
    main_gui.cpp
    ModeloFratura.cpp
    ModeloGeopressoes.cpp
    ModeloPetrofisico.cpp
    ParametrosSimulacao.cpp
    Poco.cpp
    Resultados.cpp
    SimuladorJanelaOperacional.cpp

output/
    graficos/
    resultado_ecd.csv
    resultados_completos.csv
    resultados_janela.csv

CMakeLists.txt
README.md
```

---

## Tecnologias utilizadas

- C++17
- Qt 6 Widgets
- CMake
- Ninja
- MSYS2 UCRT64 / MinGW
- Gnuplot
- Visual Studio Code
- PlantUML

---

## Compilação com CMake

O projeto utiliza CMake para gerar os executáveis da aplicação.

No Windows, utilizando MSYS2 UCRT64:

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;$env:PATH"
```

Defina a pasta de build:

```powershell
$build = "D:\build_simulador_janela"
```

Configure o projeto:

```powershell
& "C:\msys64\ucrt64\bin\cmake.exe" -S . -B $build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64"
```

Compile:

```powershell
& "C:\msys64\ucrt64\bin\cmake.exe" --build $build
```

---

## Executáveis

A compilação gera duas versões do programa:

### Interface gráfica

```powershell
& "D:\build_simulador_janela\simulador_gui.exe"
```

### Linha de comando

```powershell
& "D:\build_simulador_janela\simulador_cli.exe"
```

A versão gráfica é a principal interface de utilização do software.

---

## Interface gráfica

A interface desenvolvida com Qt 6 está organizada em cinco abas:

### Dados do Poço

Permite selecionar o arquivo CSV contendo os dados do poço e apresenta informações como:

- número de camadas;
- profundidade máxima;
- status do carregamento.

### Parâmetros

Permite carregar ou editar os parâmetros utilizados pelos modelos de engenharia.

### ECD

Permite informar:

- densidade da lama;
- perda de pressão;
- profundidade de avaliação.

A partir desses valores, o programa calcula e classifica a ECD.

### Resultados

Apresenta os resultados calculados para as diferentes camadas do poço em formato tabular.

### Gráficos

Permite gerar e visualizar diretamente na interface os gráficos técnicos da simulação.

---

## Gráficos gerados

O software gera sete gráficos principais:

1. Perfil sônico e tendência normal;
2. Porosidade e densidade em função da profundidade;
3. Tensão de sobrecarga;
4. Janela operacional de perfuração;
5. Comparação dos gradientes de pressão;
6. Limites operacionais de densidade de lama;
7. ECD na janela operacional.

---

## Modelos utilizados

Entre os principais modelos implementados estão:

- equação de Wyllie para estimativa da porosidade;
- integração da densidade para cálculo da tensão de sobrecarga;
- tendência normal de compactação;
- método de Eaton para pressão de poros;
- modelo baseado na tensão horizontal mínima para gradiente de fratura;
- cálculo da ECD a partir da densidade da lama e da perda de pressão.

---

## Fluxo geral da simulação

```text
Dados do Poço
Parâmetros da Simulação
Petrofísica
Geopressões
Gradiente de Fratura
Janela Operacional
ECD
Resultados
Gráficos e Exportação
```

---

## Arquivos de entrada

Os arquivos principais utilizados pelo caso de referência estão na pasta:

```text
data/
```

São eles:

```text
dados_poco.csv
parametros_simulacao.csv
```

---

## Arquivos de saída

Os resultados são armazenados na pasta:

```text
output/
```

Entre os arquivos produzidos estão:

```text
resultados_janela.csv
resultado_ecd.csv
resultados_completos.csv
```

Os gráficos são armazenados em:

```text
output/graficos/
```

---

## Caso de referência

Para o conjunto de dados utilizado durante o desenvolvimento, o programa apresenta como valores de referência aproximadamente:

```text
Profundidade solicitada: 4180.000 m
Camada avaliada:         4178.423905 m

ECD: 15.274236 lb/gal
Gp:  14.608955 lb/gal
Gf:  15.568016 lb/gal
```

Classificação:

```text
ECD dentro da janela operacional
(Gp < ECD < Gf)
```

---

## Projeto acadêmico

Software desenvolvido para a disciplina **Projeto de Software Aplicado à Engenharia**, utilizando conceitos de:

- especificação de software;
- análise orientada a objetos;
- UML;
- projeto orientado a objetos;
- arquitetura de software;
- implementação em C++;
- interface gráfica;
- testes e documentação.

O desenvolvimento foi realizado de forma incremental, com acompanhamento das diferentes etapas do projeto por meio do GitHub.