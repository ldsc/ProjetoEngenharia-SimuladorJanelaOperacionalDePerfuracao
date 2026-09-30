// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "ModeloFratura.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <stdexcept>

ModeloFratura::ModeloFratura(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros) {
}

// ==========================================================
// TENSÃO HORIZONTAL MÍNIMA
//
// Shmin = [nu / (1 - nu)] * (sigmaV - Pp) + Pp
// ==========================================================

double ModeloFratura::calcularTensaoHorizontalMinima(
    const Camada& camada
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloFratura::calcularTensaoHorizontalMinima ainda nao implementado.");
}

// ==========================================================
// GRADIENTE DE FRATURA
//
// Gf(psi/ft) = Shmin / H(ft)
//
// Gf(lb/gal) = Gf(psi/ft) / 0.052
// ==========================================================

double ModeloFratura::calcularGradienteFratura(
    const Camada& camada
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloFratura::calcularGradienteFratura ainda nao implementado.");
}

// ==========================================================
// PROCESSAMENTO COMPLETO DO POÇO
// ==========================================================

void ModeloFratura::processarPoco(
    Poco& poco
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloFratura::processarPoco ainda nao implementado.");
}
