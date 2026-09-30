#include "SimuladorJanelaOperacional.h"
#include <iostream>
#include <stdexcept>
int main() {
    SimuladorJanelaOperacional simulador;
    simulador.getPoco().adicionarCamada(Camada(1, 1000.0, 1100.0, 100.0));
    std::cout << "Etapa 1: estrutura C++ das 10 classes.\n";
    std::cout << "Camadas cadastradas: " << simulador.getPoco().obterNumeroCamadas() << '\n';
    std::cout << "Parametros validos: " << simulador.getParametros().validarParametros() << '\n';
    try { simulador.executarSimulacao(); }
    catch (const std::logic_error& e) { std::cout << "Pendente: " << e.what() << '\n'; }
}
