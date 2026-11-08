#include "CalculadoraECD.h"

#include <stdexcept>


namespace {

constexpr double FT_PER_M = 3.28084;

constexpr double PSI_FT_PER_LB_GAL = 0.052;

}


// ==========================================================
// CONSTRUTORES
// ==========================================================

CalculadoraECD::CalculadoraECD()
    : densidadeLama(0.0),
      perdaPressao(0.0),
      profundidade(0.0)
{
}


CalculadoraECD::CalculadoraECD(
    double densidadeLama,
    double perdaPressao,
    double profundidade
)
    : densidadeLama(densidadeLama),
      perdaPressao(perdaPressao),
      profundidade(profundidade)
{
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

    if (
        !validarParametros()
    ) {

        throw std::invalid_argument(
            "Parametros invalidos para calculo da ECD."
        );
    }


    const double profundidadeFt =
        profundidade
        * FT_PER_M;


    const double ecd =
        densidadeLama
        +
        perdaPressao
        /
        (
            PSI_FT_PER_LB_GAL
            *
            profundidadeFt
        );


    return ecd;
}


// ==========================================================
// CLASSIFICAÇÃO DA ECD
// ==========================================================

std::string CalculadoraECD::avaliarJanela(
    const JanelaOperacional& janela
) const {

    const double ecd =
        calcularECD();


    const double gp =
        janela.obterLimiteInferior();


    const double gf =
        janela.obterLimiteSuperior();


    if (
        ecd <= gp
    ) {

        return
            "ECD abaixo de Gp (risco de influxo/kick)";
    }


    if (
        ecd >= gf
    ) {

        return
            "ECD acima de Gf (risco de fratura/perdas)";
    }


    return
        "ECD dentro da janela operacional (Gp < ECD < Gf)";
}