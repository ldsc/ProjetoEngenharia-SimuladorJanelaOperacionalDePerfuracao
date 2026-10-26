#ifndef MODELOGEOPRESSOES_H
#define MODELOGEOPRESSOES_H

#include "ParametrosSimulacao.h"
#include "Poco.h"

class ModeloGeopressoes {
private:
    const ParametrosSimulacao* parametros;

public:
    explicit ModeloGeopressoes(const ParametrosSimulacao& parametros);

    double calcularTendenciaNormal(double profundidade) const;
    double calcularPressaoNormal(double profundidade) const;
    double calcularPressaoPoro(const Camada& camada) const;
    double calcularGradientePoro(const Camada& camada) const;

    void calcularSobrecarga(Poco& poco) const;
    void processarPoco(Poco& poco) const;
};

#endif