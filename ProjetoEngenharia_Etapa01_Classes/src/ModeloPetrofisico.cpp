// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "ModeloPetrofisico.h"
#include <algorithm>
#include <stdexcept>
#include <stdexcept>

ModeloPetrofisico::ModeloPetrofisico(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros) {
}

// ==========================================================
// POROSIDADE DE WYLLIE
// ==========================================================

double ModeloPetrofisico::calcularPorosidade(
    double deltaT
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloPetrofisico::calcularPorosidade ainda nao implementado.");
}

// ==========================================================
// DENSIDADE BULK
// ==========================================================

double ModeloPetrofisico::calcularDensidadeBulk(
    double porosidade
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloPetrofisico::calcularDensidadeBulk ainda nao implementado.");
}

// ==========================================================
// FORMAÇÃO COM REGISTRO SÔNICO
// ==========================================================

void ModeloPetrofisico::processarCamada(
    Camada& camada
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloPetrofisico::processarCamada ainda nao implementado.");
}

// ==========================================================
// PROCESSAMENTO DO POÇO
// ==========================================================

void ModeloPetrofisico::processarPoco(
    Poco& poco
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: ModeloPetrofisico::processarPoco ainda nao implementado.");
}
