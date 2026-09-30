// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "ParametrosSimulacao.h"
#include <stdexcept>

// ==========================================================
// CONSTRUTOR
// ==========================================================

ParametrosSimulacao::ParametrosSimulacao()
    : densidadeMatriz(2.65),
      densidadeFluido(1.074),
      densidadeAguaMar(1.03),
      densidadeSedimento(2.00),

      deltaTMatriz(55.0),
      deltaTFluido(207.0),

      porosidadeSedimento(0.35),
      porosidadeMinima(0.05),
      porosidadeMaxima(0.45),

      gradienteHidrostaticoNormal(0.465),
      expoenteEaton(3.0),
      coeficientePoisson(0.25),
      deltaTReferencia(150.0),
      constanteCompactacao(0.0001),

      densidadeLama(13.90),
      perdaPressaoECD(980.0),
      profundidadeECD(4180.0) {
}

// ==========================================================
// VALIDAÇÃO
// ==========================================================

bool ParametrosSimulacao::validarParametros() const {

    return

        // PETROFÍSICA

        densidadeMatriz > 0.0

        &&

        densidadeFluido > 0.0

        &&

        densidadeAguaMar > 0.0

        &&

        densidadeSedimento > 0.0

        &&

        deltaTMatriz > 0.0

        &&

        deltaTFluido > deltaTMatriz

        &&

        porosidadeSedimento >= 0.0

        &&

        porosidadeSedimento <= 1.0

        &&

        porosidadeMinima >= 0.0

        &&

        porosidadeMaxima <= 1.0

        &&

        porosidadeMinima <= porosidadeMaxima


        // GEOPRESSÕES

        &&

        gradienteHidrostaticoNormal > 0.0

        &&

        expoenteEaton > 0.0

        &&

        coeficientePoisson > 0.0

        &&

        coeficientePoisson < 0.5

        &&

        deltaTReferencia > 0.0

        &&

        constanteCompactacao >= 0.0


        // ECD

        &&

        densidadeLama > 0.0

        &&

        perdaPressaoECD >= 0.0

        &&

        profundidadeECD > 0.0;
}

// ==========================================================
// SETTERS - PETROFÍSICA
// ==========================================================

void ParametrosSimulacao::definirDensidadeMatriz(
    double valor
) {

    densidadeMatriz =
        valor;
}

void ParametrosSimulacao::definirDensidadeFluido(
    double valor
) {

    densidadeFluido =
        valor;
}

void ParametrosSimulacao::definirDensidadeAguaMar(
    double valor
) {

    densidadeAguaMar =
        valor;
}

void ParametrosSimulacao::definirDensidadeSedimento(
    double valor
) {

    densidadeSedimento =
        valor;
}

void ParametrosSimulacao::definirDeltaTMatriz(
    double valor
) {

    deltaTMatriz =
        valor;
}

void ParametrosSimulacao::definirDeltaTFluido(
    double valor
) {

    deltaTFluido =
        valor;
}

void ParametrosSimulacao::definirPorosidadeSedimento(
    double valor
) {

    porosidadeSedimento =
        valor;
}

void ParametrosSimulacao::definirLimitesPorosidade(
    double minimo,
    double maximo
) {

    porosidadeMinima =
        minimo;


    porosidadeMaxima =
        maximo;
}

// ==========================================================
// SETTERS - GEOPRESSÕES
// ==========================================================

void ParametrosSimulacao::definirGradienteHidrostatico(
    double valor
) {

    gradienteHidrostaticoNormal =
        valor;
}

void ParametrosSimulacao::definirExpoenteEaton(
    double valor
) {

    expoenteEaton =
        valor;
}

void ParametrosSimulacao::definirCoeficientePoisson(
    double valor
) {

    coeficientePoisson =
        valor;
}

void ParametrosSimulacao::definirDeltaTReferencia(
    double valor
) {

    deltaTReferencia =
        valor;
}

void ParametrosSimulacao::definirConstanteCompactacao(
    double valor
) {

    constanteCompactacao =
        valor;
}

// ==========================================================
// SETTERS - ECD
// ==========================================================

void ParametrosSimulacao::definirDensidadeLama(
    double valor
) {

    densidadeLama =
        valor;
}

void ParametrosSimulacao::definirPerdaPressaoECD(
    double valor
) {

    perdaPressaoECD =
        valor;
}

void ParametrosSimulacao::definirProfundidadeECD(
    double valor
) {

    profundidadeECD =
        valor;
}

// ==========================================================
// GETTERS - PETROFÍSICA
// ==========================================================

double ParametrosSimulacao::getDensidadeMatriz() const {

    return
        densidadeMatriz;
}

double ParametrosSimulacao::getDensidadeFluido() const {

    return
        densidadeFluido;
}

double ParametrosSimulacao::getDensidadeAguaMar() const {

    return
        densidadeAguaMar;
}

double ParametrosSimulacao::getDensidadeSedimento() const {

    return
        densidadeSedimento;
}

double ParametrosSimulacao::getDeltaTMatriz() const {

    return
        deltaTMatriz;
}

double ParametrosSimulacao::getDeltaTFluido() const {

    return
        deltaTFluido;
}

double ParametrosSimulacao::getPorosidadeSedimento() const {

    return
        porosidadeSedimento;
}

double ParametrosSimulacao::getPorosidadeMinima() const {

    return
        porosidadeMinima;
}

double ParametrosSimulacao::getPorosidadeMaxima() const {

    return
        porosidadeMaxima;
}

// ==========================================================
// GETTERS - GEOPRESSÕES
// ==========================================================

double
ParametrosSimulacao::getGradienteHidrostaticoNormal() const {

    return
        gradienteHidrostaticoNormal;
}

double ParametrosSimulacao::getExpoenteEaton() const {

    return
        expoenteEaton;
}

double ParametrosSimulacao::getCoeficientePoisson() const {

    return
        coeficientePoisson;
}

double ParametrosSimulacao::getDeltaTReferencia() const {

    return
        deltaTReferencia;
}

double ParametrosSimulacao::getConstanteCompactacao() const {

    return
        constanteCompactacao;
}

// ==========================================================
// GETTERS - ECD
// ==========================================================

double ParametrosSimulacao::getDensidadeLama() const {

    return
        densidadeLama;
}

double ParametrosSimulacao::getPerdaPressaoECD() const {

    return
        perdaPressaoECD;
}

double ParametrosSimulacao::getProfundidadeECD() const {

    return
        profundidadeECD;
}
