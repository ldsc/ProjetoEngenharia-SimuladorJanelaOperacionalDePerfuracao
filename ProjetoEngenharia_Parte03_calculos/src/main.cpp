#include "CalculadoraECD.h"
#include "JanelaOperacional.h"
#include "ModeloFratura.h"
#include "ModeloGeopressoes.h"
#include "ModeloPetrofisico.h"
#include "ParametrosSimulacao.h"
#include "Poco.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::vector<std::string> separarCSV(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string campo;

    while (std::getline(ss, campo, ',')) {
        campos.push_back(campo);
    }

    if (!linha.empty() && linha.back() == ',') {
        campos.push_back("");
    }

    return campos;
}

bool carregarParametrosCSV(
    const std::string& caminho,
    ParametrosSimulacao& parametros
) {
    std::ifstream arquivo(caminho);

    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    std::getline(arquivo, linha); // cabeçalho

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        const auto campos = separarCSV(linha);
        if (campos.size() < 2) continue;

        const std::string& nome = campos[0];
        const double valor = std::stod(campos[1]);

        if (nome == "densidade_matriz") parametros.definirDensidadeMatriz(valor);
        else if (nome == "densidade_fluido") parametros.definirDensidadeFluido(valor);
        else if (nome == "densidade_agua_mar") parametros.definirDensidadeAguaMar(valor);
        else if (nome == "densidade_sedimento") parametros.definirDensidadeSedimento(valor);
        else if (nome == "delta_t_matriz") parametros.definirDeltaTMatriz(valor);
        else if (nome == "delta_t_fluido") parametros.definirDeltaTFluido(valor);
        else if (nome == "porosidade_sedimento") parametros.definirPorosidadeSedimento(valor);
        else if (nome == "gradiente_hidrostatico") parametros.definirGradienteHidrostatico(valor);
        else if (nome == "expoente_eaton") parametros.definirExpoenteEaton(valor);
        else if (nome == "coeficiente_poisson") parametros.definirCoeficientePoisson(valor);
        else if (nome == "delta_t_referencia") parametros.definirDeltaTReferencia(valor);
        else if (nome == "constante_compactacao") parametros.definirConstanteCompactacao(valor);
        else if (nome == "densidade_lama") parametros.definirDensidadeLama(valor);
        else if (nome == "perda_pressao_ecd") parametros.definirPerdaPressaoECD(valor);
        else if (nome == "profundidade_ecd") parametros.definirProfundidadeECD(valor);
    }

    // Os limites de porosidade permanecem nos defaults desta etapa.
    return parametros.validarParametros();
}

bool carregarDadosCSV(
    const std::string& caminho,
    Poco& poco
) {
    std::ifstream arquivo(caminho);

    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;
    std::getline(arquivo, linha); // cabeçalho

    double topo = 0.0;
    int indice = 0;

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        const auto campos = separarCSV(linha);
        if (campos.size() < 2 || campos[0].empty()) continue;

        const double base = std::stod(campos[0]);

        double deltaT = std::numeric_limits<double>::quiet_NaN();
        if (!campos[1].empty()) {
            deltaT = std::stod(campos[1]);
        }

        TipoCamada tipo = TipoCamada::FORMACAO;
        if (campos.size() >= 3 && !campos[2].empty()) {
            tipo = Camada::converterTipo(campos[2]);
        }

        poco.adicionarCamada(
            Camada(indice, topo, base, deltaT, tipo)
        );

        topo = base;
        ++indice;
    }

    poco.calcularProfundidadeMaxima();
    return poco.validarDados();
}

}

int main() {
    try {
        std::cout << "\nSIMULADOR DE JANELA OPERACIONAL DE PERFURACAO\n";
        std::cout << "IMPLEMENTACAO PARCIAL - PARTE 3 (APROX. 75%)\n";
        std::cout << "============================================================\n\n";

        ParametrosSimulacao parametros;
        Poco poco("POCO-OFFSHORE", "offshore");

        if (!carregarParametrosCSV("data/parametros_simulacao.csv", parametros)) {
            std::cerr << "Erro ao carregar parametros.\n";
            return 1;
        }

        if (!carregarDadosCSV("data/dados_poco.csv", poco)) {
            std::cerr << "Erro ao carregar dados do poco.\n";
            return 1;
        }

        std::cout << "Dados carregados com sucesso.\n";
        std::cout << "Numero de camadas : " << poco.obterNumeroCamadas() << '\n';
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Profundidade max. : " << poco.getProfundidadeMaxima() << " m\n\n";

        ModeloPetrofisico petrofisico(parametros);
        ModeloGeopressoes geopressoes(parametros);
        ModeloFratura fratura(parametros);

        petrofisico.processarPoco(poco);
        geopressoes.processarPoco(poco);
        fratura.processarPoco(poco);

        std::cout << "[OK] Petrofisica\n";
        std::cout << "[OK] Geopressoes\n";
        std::cout << "[OK] Gradiente de fratura\n";

        std::vector<JanelaOperacional> janelas;

        for (const auto& camada : poco.getCamadas()) {
            const double gp = camada.getGradientePoro();
            const double gf = camada.getGradienteFratura();

            if (std::isfinite(gp) && std::isfinite(gf) && gf > gp) {
                janelas.emplace_back(
                    camada.getProfundidadeMedia(),
                    gp,
                    gf
                );
            }
        }

        std::cout << "[OK] Janela operacional (estrutura e classificacao)\n";
        std::cout << "Janelas validas encontradas: " << janelas.size() << "\n\n";

        if (janelas.empty()) {
            throw std::runtime_error("Nenhuma janela operacional valida.");
        }

        CalculadoraECD calculadora(
            parametros.getDensidadeLama(),
            parametros.getPerdaPressaoECD(),
            parametros.getProfundidadeECD()
        );

        const auto it = std::min_element(
            janelas.begin(),
            janelas.end(),
            [&](const JanelaOperacional& a, const JanelaOperacional& b) {
                return std::abs(a.getProfundidade() - parametros.getProfundidadeECD())
                    < std::abs(b.getProfundidade() - parametros.getProfundidadeECD());
            }
        );

        const double ecd = calculadora.calcularECD();
        const std::string classificacao = calculadora.avaliarJanela(*it);

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "ANALISE INTERMEDIARIA DE ECD\n";
        std::cout << "============================================================\n";
        std::cout << "Profundidade solicitada : " << parametros.getProfundidadeECD() << " m\n";
        std::cout << "Janela mais proxima     : " << it->getProfundidade() << " m\n";
        std::cout << "Gp                      : " << it->obterLimiteInferior() << " lb/gal\n";
        std::cout << "Gf                      : " << it->obterLimiteSuperior() << " lb/gal\n";
        std::cout << "ECD                     : " << ecd << " lb/gal\n";
        std::cout << "Classificacao           : " << classificacao << "\n\n";

        std::cout << "ETAPAS AINDA EM IMPLEMENTACAO\n";
        std::cout << "============================================================\n";
        std::cout << "[ ] Classe Resultados e consolidacao final\n";
        std::cout << "[ ] Controlador SimuladorJanelaOperacional completo\n";
        std::cout << "[ ] Exportacao automatica dos CSVs\n";
        std::cout << "[ ] Interface grafica Qt\n";
        std::cout << "[ ] Geracao e visualizacao dos graficos\n\n";

        std::cout << "PARTE 3 CONCLUIDA COM SUCESSO.\n";
        return 0;
    }
    catch (const std::exception& erro) {
        std::cerr << "\nERRO: " << erro.what() << '\n';
        return 1;
    }
}
