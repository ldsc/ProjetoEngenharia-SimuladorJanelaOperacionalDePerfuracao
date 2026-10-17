#include "Camada.h"
#include "ModeloGeopressoes.h"
#include "ModeloPetrofisico.h"
#include "ParametrosSimulacao.h"
#include "Poco.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string limparTexto(std::string texto) {
    texto.erase(
        std::remove_if(
            texto.begin(),
            texto.end(),
            [](unsigned char c) {
                return c == '\r' || c == '\n';
            }
        ),
        texto.end()
    );

    auto primeiro = std::find_if(
        texto.begin(),
        texto.end(),
        [](unsigned char c) {
            return !std::isspace(c);
        }
    );

    auto ultimo = std::find_if(
        texto.rbegin(),
        texto.rend(),
        [](unsigned char c) {
            return !std::isspace(c);
        }
    ).base();

    if (primeiro >= ultimo) {
        return "";
    }

    return std::string(primeiro, ultimo);
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
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string nome;
        std::string valorTexto;

        std::getline(ss, nome, ',');
        std::getline(ss, valorTexto, ',');

        nome = limparTexto(nome);
        valorTexto = limparTexto(valorTexto);

        if (nome.empty() || valorTexto.empty()) {
            continue;
        }

        const double valor = std::stod(valorTexto);

        if (nome == "densidade_matriz") {
            parametros.definirDensidadeMatriz(valor);
        }
        else if (nome == "densidade_fluido") {
            parametros.definirDensidadeFluido(valor);
        }
        else if (nome == "densidade_agua_mar") {
            parametros.definirDensidadeAguaMar(valor);
        }
        else if (nome == "densidade_sedimento") {
            parametros.definirDensidadeSedimento(valor);
        }
        else if (nome == "delta_t_matriz") {
            parametros.definirDeltaTMatriz(valor);
        }
        else if (nome == "delta_t_fluido") {
            parametros.definirDeltaTFluido(valor);
        }
        else if (nome == "porosidade_sedimento") {
            parametros.definirPorosidadeSedimento(valor);
        }
        else if (nome == "gradiente_hidrostatico") {
            parametros.definirGradienteHidrostatico(valor);
        }
        else if (nome == "expoente_eaton") {
            parametros.definirExpoenteEaton(valor);
        }
        else if (nome == "coeficiente_poisson") {
            parametros.definirCoeficientePoisson(valor);
        }
        else if (nome == "delta_t_referencia") {
            parametros.definirDeltaTReferencia(valor);
        }
        else if (nome == "constante_compactacao") {
            parametros.definirConstanteCompactacao(valor);
        }
        else if (nome == "densidade_lama") {
            parametros.definirDensidadeLama(valor);
        }
        else if (nome == "perda_pressao_ecd") {
            parametros.definirPerdaPressaoECD(valor);
        }
        else if (nome == "profundidade_ecd") {
            parametros.definirProfundidadeECD(valor);
        }
    }

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
    int numeroLinha = 1;

    while (std::getline(arquivo, linha)) {
        ++numeroLinha;

        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string profundidadeTexto;
        std::string sonicoTexto;
        std::string tipoTexto;

        std::getline(ss, profundidadeTexto, ',');
        std::getline(ss, sonicoTexto, ',');
        std::getline(ss, tipoTexto, ',');

        profundidadeTexto = limparTexto(profundidadeTexto);
        sonicoTexto = limparTexto(sonicoTexto);
        tipoTexto = limparTexto(tipoTexto);

        if (profundidadeTexto.empty()) {
            throw std::runtime_error(
                "Profundidade ausente na linha " +
                std::to_string(numeroLinha) + "."
            );
        }

        const double base = std::stod(profundidadeTexto);

        if (base <= topo) {
            throw std::runtime_error(
                "As profundidades devem estar em ordem crescente."
            );
        }

        double deltaT = std::numeric_limits<double>::quiet_NaN();

        if (!sonicoTexto.empty()) {
            deltaT = std::stod(sonicoTexto);
        }

        TipoCamada tipo = TipoCamada::DESCONHECIDA;

        if (!tipoTexto.empty()) {
            tipo = Camada::converterTipo(tipoTexto);
        }
        else if (std::isfinite(deltaT)) {
            tipo = TipoCamada::FORMACAO;
        }

        if (tipo == TipoCamada::DESCONHECIDA) {
            throw std::runtime_error(
                "Tipo de camada ausente ou invalido na linha " +
                std::to_string(numeroLinha) + "."
            );
        }

        poco.adicionarCamada(
            Camada(
                indice,
                topo,
                base,
                deltaT,
                tipo
            )
        );

        topo = base;
        ++indice;
    }

    poco.calcularProfundidadeMaxima();
    return poco.validarDados();
}

} // namespace

int main() {
    try {
        std::cout
            << "\nSIMULADOR DE JANELA OPERACIONAL DE PERFURACAO\n"
            << "IMPLEMENTACAO PARCIAL - ETAPA INTERMEDIARIA\n"
            << "============================================================\n\n";

        ParametrosSimulacao parametros;
        Poco poco("POCO-OFFSHORE", "offshore");

        if (!carregarParametrosCSV(
                "data/parametros_simulacao.csv",
                parametros
            )) {
            std::cerr
                << "Erro ao carregar os parametros da simulacao.\n";
            return 1;
        }

        if (!carregarDadosCSV(
                "data/dados_poco.csv",
                poco
            )) {
            std::cerr
                << "Erro ao carregar os dados do poco.\n";
            return 1;
        }

        std::cout
            << "Dados carregados com sucesso.\n"
            << "Numero de camadas   : "
            << poco.obterNumeroCamadas()
            << '\n'
            << "Profundidade maxima : "
            << std::fixed
            << std::setprecision(2)
            << poco.getProfundidadeMaxima()
            << " m\n\n";

        ModeloPetrofisico modeloPetrofisico(parametros);
        ModeloGeopressoes modeloGeopressoes(parametros);

        modeloPetrofisico.processarPoco(poco);

        std::cout
            << "[OK] Petrofisica implementada\n"
            << "     - Porosidade pelo modelo de Wyllie\n"
            << "     - Densidade bulk\n";

        modeloGeopressoes.processarPoco(poco);

        std::cout
            << "[OK] Geopressoes implementadas\n"
            << "     - Tensao de sobrecarga\n"
            << "     - Tendencia normal sonica\n"
            << "     - Pressao de poros pelo metodo de Eaton\n"
            << "     - Gradiente de poros\n\n";

        std::cout
            << "AMOSTRA DOS RESULTADOS INTERMEDIARIOS\n"
            << "============================================================\n"
            << std::left
            << std::setw(7)  << "Camada"
            << std::setw(14) << "Tipo"
            << std::setw(14) << "Prof.(m)"
            << std::setw(12) << "Phi"
            << std::setw(14) << "RhoBulk"
            << std::setw(14) << "SigmaV"
            << std::setw(14) << "Gp(ppg)"
            << '\n';

        int exibidas = 0;

        for (const auto& camada : poco.getCamadas()) {
            if (exibidas >= 10) {
                break;
            }

            std::cout
                << std::left
                << std::setw(7)  << camada.getIndice()
                << std::setw(14) << camada.getTipoTexto()
                << std::setw(14) << std::fixed << std::setprecision(2)
                << camada.getProfundidadeMedia()
                << std::setw(12) << std::setprecision(4)
                << camada.getPorosidade()
                << std::setw(14) << std::setprecision(4)
                << camada.getDensidadeBulk()
                << std::setw(14) << std::setprecision(2)
                << camada.getTensaoSobrecarga();

            if (std::isfinite(camada.getGradientePoro())) {
                std::cout
                    << std::setw(14)
                    << std::setprecision(4)
                    << camada.getGradientePoro();
            }
            else {
                std::cout
                    << std::setw(14)
                    << "-";
            }

            std::cout << '\n';
            ++exibidas;
        }

        std::cout
            << "\nETAPAS AINDA EM IMPLEMENTACAO\n"
            << "============================================================\n"
            << "[ ] Gradiente de fratura\n"
            << "[ ] Janela operacional de perfuracao\n"
            << "[ ] Calculo e classificacao da ECD\n"
            << "[ ] Consolidacao/exportacao dos resultados\n"
            << "[ ] Integracao completa do controlador\n"
            << "[ ] Interface grafica Qt\n"
            << "[ ] Geracao e visualizacao dos graficos\n\n"
            << "ETAPA PARCIAL CONCLUIDA COM SUCESSO.\n";

        return 0;
    }
    catch (const std::exception& erro) {
        std::cerr
            << "\nERRO: "
            << erro.what()
            << '\n';
        return 1;
    }
}
