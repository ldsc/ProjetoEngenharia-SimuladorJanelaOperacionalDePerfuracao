// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "JanelaOperacional.h"
#include <cmath>
#include <limits>
#include <stdexcept>

JanelaOperacional::JanelaOperacional()
    : profundidade(0.0),
      gradientePoro(0.0),
      gradienteFratura(0.0),
      larguraJanela(0.0) {
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
      ) {
}

// ==========================================================
// LARGURA DA JANELA
// ==========================================================

double JanelaOperacional::calcularLargura() {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: JanelaOperacional::calcularLargura ainda nao implementado.");
}

// ==========================================================
// VERIFICA SE O PESO DE LAMA ESTÁ DENTRO DA JANELA
// ==========================================================

bool JanelaOperacional::verificarPesoLama(
    double pesoLama
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: JanelaOperacional::verificarPesoLama ainda nao implementado.");
}

// ==========================================================
// CLASSIFICAÇÃO OPERACIONAL
// ==========================================================

std::string JanelaOperacional::classificarPesoLama(
    double pesoLama
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: JanelaOperacional::classificarPesoLama ainda nao implementado.");
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
