// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "ModeloGeopressoes.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <stdexcept>

ModeloGeopressoes::ModeloGeopressoes(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros) {
}

// ==========================================================
// TENDÊNCIA NORMAL DO PERFIL SÔNICO
// Δtn = Δt0 * exp(-k * z)
// profundidade recebida em metros
// ==========================================================

double ModeloGeopressoes::calcularTendenciaNormal(
    double profundidade
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::calcularTendenciaNormal ainda nao implementado.");
}

// ==========================================================
// PRESSÃO NORMAL HIDROSTÁTICA
// Pn = GradNormal * H(ft)
// ==========================================================

double ModeloGeopressoes::calcularPressaoNormal(
    double profundidade
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::calcularPressaoNormal ainda nao implementado.");
}

// ==========================================================
// PRESSÃO DE PORO - MÉTODO DE EATON
//
// Pp = σv - (σv - Pn) * (Δtn / Δt)^alpha
// ==========================================================

double ModeloGeopressoes::calcularPressaoPoro(
    const Camada& camada
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::calcularPressaoPoro ainda nao implementado.");
}

// ==========================================================
// GRADIENTE DE PRESSÃO DE PORO
//
// Gp(psi/ft) = Pp / H
//
// Gp(lb/gal) = Gp(psi/ft) / 0.052
// ==========================================================

double ModeloGeopressoes::calcularGradientePoro(
    const Camada& camada
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::calcularGradientePoro ainda nao implementado.");
}

// ==========================================================
// TENSÃO DE SOBRECARGA
//
// Δσv = 0.052 * rho(lb/gal) * ΔH(ft)
//
// σv = soma acumulada
// ==========================================================

void ModeloGeopressoes::calcularSobrecarga(
    Poco& poco
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::calcularSobrecarga ainda nao implementado.");
}

// ==========================================================
// PROCESSAMENTO COMPLETO DO POÇO
// ==========================================================

void ModeloGeopressoes::processarPoco(
    Poco& poco
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloGeopressoes::processarPoco ainda nao implementado.");
}
