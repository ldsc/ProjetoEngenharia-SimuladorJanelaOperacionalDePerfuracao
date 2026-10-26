#ifndef MODELOFRATURA_H
#define MODELOFRATURA_H

#include "ParametrosSimulacao.h"
#include "Poco.h"

class ModeloFratura {
private:
    const ParametrosSimulacao* parametros;

public:
    explicit ModeloFratura(const ParametrosSimulacao& parametros);

    double calcularTensaoHorizontalMinima(const Camada& camada) const;
    double calcularGradienteFratura(const Camada& camada) const;
    void processarPoco(Poco& poco) const;
};

#endif
