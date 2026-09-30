// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "SimuladorJanelaOperacional.h"
#include <cctype>
#include <cmath>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdexcept>

// ==========================================================
// CONSTRUTOR
// ==========================================================

SimuladorJanelaOperacional::
SimuladorJanelaOperacional()
    : poco(
        "POCO-OFFSHORE",
        "offshore"
      ) {
}

// ==========================================================
// CARREGAMENTO DOS DADOS DO POÇO
// ==========================================================

bool
SimuladorJanelaOperacional::carregarDadosCSV(
    const std::string& caminhoArquivo
) {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::carregarDadosCSV ainda nao implementado.");
}

// ==========================================================
// CARREGAMENTO DOS PARÂMETROS
// ==========================================================

bool
SimuladorJanelaOperacional::carregarParametrosCSV(
    const std::string& caminhoArquivo
) {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::carregarParametrosCSV ainda nao implementado.");
}

// ==========================================================
// GETTERS
// ==========================================================

Poco&
SimuladorJanelaOperacional::getPoco() {

    return
        poco;
}

ParametrosSimulacao&
SimuladorJanelaOperacional::getParametros() {

    return
        parametros;
}

Resultados&
SimuladorJanelaOperacional::getResultados() {

    return
        resultados;
}

// ==========================================================
// PETROFÍSICA
// ==========================================================

void
SimuladorJanelaOperacional::
calcularPetrofisica() {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::calcularPetrofisica ainda nao implementado.");
}

// ==========================================================
// GEOPRESSÕES
// ==========================================================

void
SimuladorJanelaOperacional::
calcularGeopressoes() {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::calcularGeopressoes ainda nao implementado.");
}

// ==========================================================
// FRATURA
// ==========================================================

void
SimuladorJanelaOperacional::
calcularFratura() {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::calcularFratura ainda nao implementado.");
}

// ==========================================================
// JANELAS
// ==========================================================

void
SimuladorJanelaOperacional::
determinarJanelas() {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::determinarJanelas ainda nao implementado.");
}

// ==========================================================
// ECD
// ==========================================================

void
SimuladorJanelaOperacional::avaliarECD(
    double densidadeLama,
    double perdaPressao,
    double profundidade
) {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::avaliarECD ainda nao implementado.");
}

// ==========================================================
// EXECUÇÃO COMPLETA
// ==========================================================

void
SimuladorJanelaOperacional::
executarSimulacao() {

    calcularPetrofisica();

    calcularGeopressoes();

    calcularFratura();

    determinarJanelas();


    resultados.definirSimulacaoValida(
        true
    );
}

// ==========================================================
// EXPORTAÇÃO
// ==========================================================

bool
SimuladorJanelaOperacional::
exportarResultados(
    const std::string& caminhoArquivo
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: SimuladorJanelaOperacional::exportarResultados ainda nao implementado.");
}
