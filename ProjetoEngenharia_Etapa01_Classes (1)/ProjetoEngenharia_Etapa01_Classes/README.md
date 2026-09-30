# Simulador de Janela Operacional de Perfuração
## Etapa 01 — definição das classes

Autor: Augusto Caio Rotte Fernandes Oliveira  
Disciplina: Projeto de Software de Engenharia — 2026/02

Recorte estrutural extraído da versão atual do projeto para revisão por etapas. Esta pasta apresenta as classes e seus contratos separadamente das implementações de cálculo e da interface gráfica já existentes no projeto principal. Ela não representa um registro histórico de quando cada parte foi desenvolvida.

### Conteúdo desta revisão

- Dez classes em arquivos `.h` e `.cpp`, preservando os nomes, atributos e assinaturas do projeto anexado.
- Encapsulamento, construtores, acesso aos dados, cadastro de camadas e validações básicas.
- Relações de composição e associação entre os objetos.
- Sequência de execução declarada no simulador.
- Programa demonstrativo e configuração para compilação no VS Code.

Os métodos de cálculo, importação, classificação operacional, exportação e geração de gráficos foram deixados como pontos de implementação neste recorte. Eles lançam `std::logic_error`, com identificação do método, para não produzir resultados fictícios. O programa demonstrativo identifica a primeira operação pendente.

### Classes

1. SimuladorJanelaOperacional
2. Poco
3. Camada
4. ParametrosSimulacao
5. ModeloPetrofisico
6. ModeloGeopressoes
7. ModeloFratura
8. CalculadoraECD
9. JanelaOperacional
10. Resultados

### Compilação no VS Code

Extraia o ZIP e abra esta pasta. São necessários um compilador C++17 e CMake. Instale as extensões recomendadas e use Ctrl+Shift+B, ou execute:

```sh
cmake -S . -B build
cmake --build build
```

Linux: `./build/etapa1`. Windows com MinGW: `.\build\etapa1.exe`. Windows com Visual Studio: `.\build\Debug\etapa1.exe`.

Alternativa com g++ instalado, sem CMake:

```sh
g++ -std=c++17 -I include src/*.cpp -o etapa1
```

Execute `./etapa1` no Linux ou `.\etapa1.exe` no Windows.

### Revisões seguintes

As próximas revisões podem apresentar e validar os modelos petrofísicos, as geopressões, a janela operacional e ECD, os resultados e a interface gráfica. Cada revisão deve indicar o que foi incluído, ajustado e verificado nela.

### Verificação desta entrega

As dez interfaces foram comparadas com o ZIP mais recente recebido e são idênticas. O código deste recorte foi compilado com g++ em C++17 e executado. O CMake não foi executado no ambiente de verificação, pois não está instalado.

A correspondência estrutural está descrita em `docs/Correspondencia.md`. O anexo não contém arquivos UML; portanto, a equivalência exata com as imagens dos diagramas ainda não foi certificada. Esta pasta deve ser mantida separada do projeto principal para evitar substituir implementações completas por este recorte.
