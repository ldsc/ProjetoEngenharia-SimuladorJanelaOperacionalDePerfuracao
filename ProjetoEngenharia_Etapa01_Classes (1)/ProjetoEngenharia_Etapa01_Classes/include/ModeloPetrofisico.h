#ifndef MODELOPETROFISICO_H
#define MODELOPETROFISICO_H

#include "Camada.h"
#include "ParametrosSimulacao.h"
#include "Poco.h"

class ModeloPetrofisico {
private:
    const ParametrosSimulacao* parametros;

public:
    explicit ModeloPetrofisico(const ParametrosSimulacao& parametros);

    double calcularPorosidade(double deltaT) const;
    double calcularDensidadeBulk(double porosidade) const;
    void processarCamada(Camada& camada) const;
    void processarPoco(Poco& poco) const;
};

#endif
