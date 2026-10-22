#include "JanelaOperacional.h"

#include <cmath>
#include <limits>


JanelaOperacional::JanelaOperacional()
    : profundidade(0.0),
      gradientePoro(0.0),
      gradienteFratura(0.0),
      larguraJanela(0.0)
{
}


JanelaOperacional::JanelaOperacional(
    double profundidade,
    double gradientePoro,
    double gradienteFratura
)
    : profundidade(profundidade),
      gradientePoro(gradientePoro),
      gradienteFratura(gradienteFratura),
      larguraJanela(
          gradienteFratura - gradientePoro
      )
{
}


// ==========================================================
// LARGURA DA JANELA
// ==========================================================

double JanelaOperacional::calcularLargura() {

    if (
        std::isnan(gradientePoro)
        ||
        std::isnan(gradienteFratura)
    ) {

        larguraJanela =
            std::numeric_limits<double>::quiet_NaN();

        return larguraJanela;
    }


    larguraJanela =
        gradienteFratura
        - gradientePoro;


    return larguraJanela;
}


// ==========================================================
// VERIFICA SE O PESO DE LAMA ESTÁ DENTRO DA JANELA
// ==========================================================

bool JanelaOperacional::verificarPesoLama(
    double pesoLama
) const {

    return
        pesoLama > gradientePoro
        &&
        pesoLama < gradienteFratura;
}


// ==========================================================
// CLASSIFICAÇÃO OPERACIONAL
// ==========================================================

std::string JanelaOperacional::classificarPesoLama(
    double pesoLama
) const {

    if (
        pesoLama < gradientePoro
    ) {

        return "Risco de kick";
    }


    if (
        pesoLama > gradienteFratura
    ) {

        return "Risco de fratura/perdas";
    }


    if (
        pesoLama == gradientePoro
        ||
        pesoLama == gradienteFratura
    ) {

        return "Condicao limite";
    }


    return "Condicao segura";
}


// ==========================================================
// GETTERS
// ==========================================================

double JanelaOperacional::obterLimiteInferior() const {
    return gradientePoro;
}


double JanelaOperacional::obterLimiteSuperior() const {
    return gradienteFratura;
}


double JanelaOperacional::getProfundidade() const {
    return profundidade;
}


double JanelaOperacional::getLarguraJanela() const {
    return larguraJanela;
}