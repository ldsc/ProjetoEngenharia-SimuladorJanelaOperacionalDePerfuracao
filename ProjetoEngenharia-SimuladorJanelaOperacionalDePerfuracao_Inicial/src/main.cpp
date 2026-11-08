#include "SimuladorJanelaOperacional.h"

#include <iomanip>
#include <iostream>


int main() {

    try {

        SimuladorJanelaOperacional simulador;


        std::cout
            << "\nSIMULADOR DE JANELA OPERACIONAL DE PERFURACAO\n";

        std::cout
            << "========================================================\n\n";


        // ==================================================
        // PARÂMETROS
        // ==================================================

        if (
            !simulador.carregarParametrosCSV(
                "data/parametros_simulacao.csv"
            )
        ) {

            std::cerr
                << "Erro ao abrir data/parametros_simulacao.csv\n";

            return 1;
        }


        std::cout
            << "Parametros carregados com sucesso.\n";


        // ==================================================
        // DADOS DO POÇO
        // ==================================================

        if (
            !simulador.carregarDadosCSV(
                "data/dados_poco.csv"
            )
        ) {

            std::cerr
                << "Erro ao abrir data/dados_poco.csv\n";

            return 1;
        }


        std::cout
            << "Dados do poco carregados com sucesso.\n";


        std::cout
            << "Numero de camadas: "
            << simulador
                   .getPoco()
                   .obterNumeroCamadas()
            << '\n';


        std::cout
            << "Profundidade maxima: "
            << std::fixed
            << std::setprecision(2)
            << simulador
                   .getPoco()
                   .getProfundidadeMaxima()
            << " m\n\n";


        // ==================================================
        // PARÂMETROS CARREGADOS
        // ==================================================

        const auto& parametros =
            simulador.getParametros();


        std::cout
            << "PARAMETROS DA SIMULACAO\n";

        std::cout
            << "========================================================\n";


        std::cout
            << std::fixed
            << std::setprecision(6);


        std::cout
            << "Densidade da matriz     : "
            << parametros.getDensidadeMatriz()
            << " g/cm3\n";


        std::cout
            << "Densidade do fluido     : "
            << parametros.getDensidadeFluido()
            << " g/cm3\n";


        std::cout
            << "Delta t matriz          : "
            << parametros.getDeltaTMatriz()
            << " us/ft\n";


        std::cout
            << "Delta t fluido          : "
            << parametros.getDeltaTFluido()
            << " us/ft\n";


        std::cout
            << "Expoente de Eaton       : "
            << parametros.getExpoenteEaton()
            << '\n';


        std::cout
            << "Coeficiente de Poisson  : "
            << parametros.getCoeficientePoisson()
            << '\n';


        std::cout
            << "Constante compactacao   : "
            << parametros.getConstanteCompactacao()
            << '\n';


        std::cout
            << "Densidade da lama       : "
            << parametros.getDensidadeLama()
            << " lb/gal\n";


        std::cout
            << "Perda de pressao ECD    : "
            << parametros.getPerdaPressaoECD()
            << " psi\n";


        std::cout
            << "Profundidade ECD        : "
            << parametros.getProfundidadeECD()
            << " m\n\n";


        // ==================================================
        // SIMULAÇÃO
        // ==================================================

        simulador.executarSimulacao();


        std::cout
            << "Petrofisica ........ OK\n";

        std::cout
            << "Geopressoes ........ OK\n";

        std::cout
            << "Gradiente fratura .. OK\n";

        std::cout
            << "Janela operacional . OK\n\n";


        // ==================================================
        // ANÁLISE ECD
        //
        // Valores agora vêm do arquivo de parâmetros.
        // ==================================================

        simulador.avaliarECD(

            parametros.getDensidadeLama(),

            parametros.getPerdaPressaoECD(),

            parametros.getProfundidadeECD()
        );


        Resultados& resultados =
            simulador.getResultados();


        std::cout
            << "ANALISE DE ECD\n";

        std::cout
            << "========================================================\n";


        std::cout
            << "Profundidade solicitada : "
            << parametros.getProfundidadeECD()
            << " m\n";


        std::cout
            << "Camada avaliada         : "
            << resultados.getProfundidadeECD()
            << " m\n";


        std::cout
            << "Densidade da lama       : "
            << resultados.getDensidadeLamaECD()
            << " lb/gal\n";


        std::cout
            << "Perda de pressao        : "
            << resultados.getPerdaPressaoECD()
            << " psi\n";


        std::cout
            << "ECD calculada           : "
            << resultados.getECDCalculada()
            << " lb/gal\n";


        std::cout
            << "Gp                      : "
            << resultados.getGradientePoroECD()
            << " lb/gal\n";


        std::cout
            << "Gf                      : "
            << resultados.getGradienteFraturaECD()
            << " lb/gal\n";


        std::cout
            << "Classificacao           : "
            << resultados.getClassificacaoECD()
            << "\n\n";


        // ==================================================
        // EXPORTAÇÕES
        // ==================================================

        simulador.exportarResultados(
            "output/resultados_janela.csv"
        );


        resultados.exportarResultadoECD(
            "output/resultado_ecd.csv"
        );


        resultados.exportarDadosCompletos(

            simulador.getPoco(),

            simulador.getParametros(),

            "output/resultados_completos.csv"
        );


        // ==================================================
        // GRÁFICOS
        // ==================================================

        std::cout
            << "Gerando graficos...\n";


        const bool graficosGerados =
            resultados.gerarGraficos(

                simulador.getPoco(),

                simulador.getParametros(),

                "output/graficos"
            );


        if (
            graficosGerados
        ) {

            std::cout
                << "Graficos gerados com sucesso.\n";
        }
        else {

            std::cout
                << "Nao foi possivel gerar os graficos.\n";

            std::cout
                << "Verifique se o Gnuplot esta instalado.\n";
        }


        std::cout
            << "\nSIMULACAO CONCLUIDA COM SUCESSO.\n";


        return 0;
    }


    catch (
        const std::exception& erro
    ) {

        std::cerr
            << "\nERRO: "
            << erro.what()
            << '\n';


        return 1;
    }
}