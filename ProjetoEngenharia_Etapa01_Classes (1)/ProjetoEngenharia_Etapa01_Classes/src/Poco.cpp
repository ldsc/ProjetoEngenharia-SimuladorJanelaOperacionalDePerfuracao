// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "Poco.h"
#include <stdexcept>
#include <stdexcept>

Poco::Poco() : identificador(""), tipo(""), profundidadeMaxima(0.0) {}

Poco::Poco(const std::string& identificador, const std::string& tipo)
    : identificador(identificador), tipo(tipo), profundidadeMaxima(0.0) {}

void Poco::adicionarCamada(const Camada& camada) {
    camadas.push_back(camada);
    if (camada.getBase() > profundidadeMaxima) profundidadeMaxima = camada.getBase();
}

Camada& Poco::obterCamada(std::size_t indice) {
    if (indice >= camadas.size()) throw std::out_of_range("Indice de camada invalido.");
    return camadas[indice];
}

const Camada& Poco::obterCamada(std::size_t indice) const {
    if (indice >= camadas.size()) throw std::out_of_range("Indice de camada invalido.");
    return camadas[indice];
}

std::size_t Poco::obterNumeroCamadas() const { return camadas.size(); }

double Poco::calcularProfundidadeMaxima() {
    profundidadeMaxima = 0.0;
    for (const auto& camada : camadas) {
        if (camada.getBase() > profundidadeMaxima) profundidadeMaxima = camada.getBase();
    }
    return profundidadeMaxima;
}

bool Poco::validarDados() const {
    if (camadas.empty()) return false;
    for (const auto& camada : camadas) {
        if (camada.getTopo() < 0.0 || camada.getBase() <= camada.getTopo()) return false;
    }
    return true;
}

const std::vector<Camada>& Poco::getCamadas() const { return camadas; }

std::vector<Camada>& Poco::getCamadas() { return camadas; }

const std::string& Poco::getIdentificador() const { return identificador; }

double Poco::getProfundidadeMaxima() const { return profundidadeMaxima; }
