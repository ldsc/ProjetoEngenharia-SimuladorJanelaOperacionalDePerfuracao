#include "SimuladorJanelaOperacional.h"

#include <filesystem>
#include <iomanip>
#include <iostream>

int main() {
    try {
        std::cout << "\nSIMULADOR DE JANELA OPERACIONAL DE PERFURACAO\n";
        std::cout << "IMPLEMENTACAO AVANCADA - PARTE 4 (APROX. 90%)\n";
        std::cout << "============================================================\n\n";

        SimuladorJanelaOperacional simulador;

        if (!simulador.carregarParametrosCSV("data/parametros_simulacao.csv")) {
            std::cerr << "Erro ao carregar parametros.\n";
            return 1;
        }

        if (!simulador.carregarDadosCSV("data/dados_poco.csv")) {
            std::cerr << "Erro ao carregar dados do poco.\n";
            return 1;
        }

        std::cout << "[OK] Parametros carregados\n";
        std::cout << "[OK] Dados do poco carregados\n";
        std::cout << "Numero de camadas : " << simulador.getPoco().obterNumeroCamadas() << '\n';
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Profundidade max. : " << simulador.getPoco().getProfundidadeMaxima() << " m\n\n";

        simulador.executarSimulacao();

        std::cout << "[OK] Petrofisica\n";
        std::cout << "[OK] Geopressoes\n";
        std::cout << "[OK] Gradiente de fratura\n";
        std::cout << "[OK] Janela operacional\n";
        std::cout << "[OK] Controlador integrado\n";

        auto& parametros = simulador.getParametros();

        simulador.avaliarECD(
            parametros.getDensidadeLama(),
            parametros.getPerdaPressaoECD(),
            parametros.getProfundidadeECD()
        );

        Resultados& resultados = simulador.getResultados();

        std::cout << "[OK] Calculo e classificacao da ECD\n\n";

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "RESULTADO INTEGRADO\n";
        std::cout << "============================================================\n";
        std::cout << "Profundidade solicitada : " << parametros.getProfundidadeECD() << " m\n";
        std::cout << "Camada avaliada         : " << resultados.getProfundidadeECD() << " m\n";
        std::cout << "Gp                      : " << resultados.getGradientePoroECD() << " lb/gal\n";
        std::cout << "Gf                      : " << resultados.getGradienteFraturaECD() << " lb/gal\n";
        std::cout << "ECD                     : " << resultados.getECDCalculada() << " lb/gal\n";
        std::cout << "Classificacao           : " << resultados.getClassificacaoECD() << "\n\n";

        std::filesystem::create_directories("output");

        const bool exportouJanela = simulador.exportarResultados("output/resultados_janela.csv");
        const bool exportouECD = resultados.exportarResultadoECD("output/resultado_ecd.csv");
        const bool exportouCompleto = resultados.exportarDadosCompletos(
            simulador.getPoco(),
            simulador.getParametros(),
            "output/resultados_completos.csv"
        );

        if (exportouJanela && exportouECD && exportouCompleto) {
            std::cout << "[OK] Resultados consolidados e exportados em CSV\n\n";
        }
        else {
            std::cout << "[AVISO] Alguma exportacao nao foi concluida.\n\n";
        }

        std::cout << "ETAPAS FINAIS AINDA EM IMPLEMENTACAO\n";
        std::cout << "============================================================\n";
        std::cout << "[ ] Interface grafica Qt\n";
        std::cout << "[ ] Geracao automatica dos graficos\n";
        std::cout << "[ ] Visualizacao dos graficos na interface\n";
        std::cout << "[ ] Acabamento final da experiencia do usuario\n\n";

        std::cout << "PARTE 4 CONCLUIDA COM SUCESSO.\n";
        return 0;
    }
    catch (const std::exception& erro) {
        std::cerr << "\nERRO: " << erro.what() << '\n';
        return 1;
    }
}
