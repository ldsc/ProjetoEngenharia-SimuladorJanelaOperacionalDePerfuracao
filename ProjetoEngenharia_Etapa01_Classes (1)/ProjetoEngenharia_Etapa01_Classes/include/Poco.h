#ifndef POCO_H
#define POCO_H

#include "Camada.h"
#include <string>
#include <vector>

class Poco {
private:
    std::string identificador;
    std::string tipo;
    double profundidadeMaxima;
    std::vector<Camada> camadas;

public:
    Poco();
    Poco(const std::string& identificador, const std::string& tipo);

    void adicionarCamada(const Camada& camada);
    Camada& obterCamada(std::size_t indice);
    const Camada& obterCamada(std::size_t indice) const;
    std::size_t obterNumeroCamadas() const;
    double calcularProfundidadeMaxima();
    bool validarDados() const;

    const std::vector<Camada>& getCamadas() const;
    std::vector<Camada>& getCamadas();
    const std::string& getIdentificador() const;
    double getProfundidadeMaxima() const;
};

#endif
