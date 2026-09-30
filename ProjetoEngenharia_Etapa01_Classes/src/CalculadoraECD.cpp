// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "CalculadoraECD.h"
#include <stdexcept>
#include <stdexcept>

// ==========================================================
// CONSTRUTORES
// ==========================================================

CalculadoraECD::CalculadoraECD()
    : densidadeLama(0.0),
      perdaPressao(0.0),
      profundidade(0.0) {
}

CalculadoraECD::CalculadoraECD(
    double densidadeLama,
    double perdaPressao,
    double profundidade
)
    : densidadeLama(densidadeLama),
      perdaPressao(perdaPressao),
      profundidade(profundidade) {
}

// ==========================================================
// SETTERS
// ==========================================================

void CalculadoraECD::definirDensidadeLama(
    double valor
) {

    densidadeLama = valor;
}

void CalculadoraECD::definirPerdaPressao(
    double valor
) {

    perdaPressao = valor;
}

void CalculadoraECD::definirProfundidade(
    double valor
) {

    profundidade = valor;
}

// ==========================================================
// GETTERS
// ==========================================================

double CalculadoraECD::getDensidadeLama() const {

    return densidadeLama;
}

double CalculadoraECD::getPerdaPressao() const {

    return perdaPressao;
}

double CalculadoraECD::getProfundidade() const {

    return profundidade;
}

// ==========================================================
// VALIDAÇÃO
// ==========================================================

bool CalculadoraECD::validarParametros() const {

    return
        densidadeLama > 0.0
        &&
        perdaPressao >= 0.0
        &&
        profundidade > 0.0;
}

// ==========================================================
// CÁLCULO DA ECD
//
// ECD = MW + ΔPf / (0.052 * Hft)
// ==========================================================

double CalculadoraECD::calcularECD() const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: CalculadoraECD::calcularECD ainda nao implementado.");
}

// ==========================================================
// CLASSIFICAÇÃO DA ECD
// ==========================================================

std::string CalculadoraECD::avaliarJanela(
    const JanelaOperacional& janela
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: CalculadoraECD::avaliarJanela ainda nao implementado.");
}
