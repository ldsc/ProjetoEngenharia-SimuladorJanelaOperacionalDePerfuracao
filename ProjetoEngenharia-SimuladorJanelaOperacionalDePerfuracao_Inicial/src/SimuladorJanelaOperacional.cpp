#include "SimuladorJanelaOperacional.h"

#include <cctype>
#include <cmath>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>


namespace {


// ==========================================================
// REMOVE ESPAÇOS
// ==========================================================

std::string limparTexto(
    std::string texto
) {

    while (
        !texto.empty()
        &&
        std::isspace(
            static_cast<unsigned char>(
                texto.front()
            )
        )
    ) {

        texto.erase(
            texto.begin()
        );
    }


    while (
        !texto.empty()
        &&
        std::isspace(
            static_cast<unsigned char>(
                texto.back()
            )
        )
    ) {

        texto.pop_back();
    }


    return
        texto;
}


// ==========================================================
// NORMALIZA NOME DO PARÂMETRO
// ==========================================================

std::string normalizarParametro(
    std::string texto
) {

    texto =
        limparTexto(
            texto
        );


    for (
        char& caractere :
        texto
    ) {

        caractere =
            static_cast<char>(
                std::tolower(
                    static_cast<unsigned char>(
                        caractere
                    )
                )
            );
    }


    return
        texto;
}


// ==========================================================
// DETECTA "," OU ";"
// ==========================================================

char detectarSeparador(
    const std::string& linha
) {

    if (
        linha.find(';')
        !=
        std::string::npos
    ) {

        return ';';
    }


    return ',';
}


}


// ==========================================================
// CONSTRUTOR
// ==========================================================

SimuladorJanelaOperacional::
SimuladorJanelaOperacional()
    : poco(
        "POCO-OFFSHORE",
        "offshore"
      )
{
}


// ==========================================================
// CARREGAMENTO DOS DADOS DO POÇO
// ==========================================================

bool
SimuladorJanelaOperacional::carregarDadosCSV(
    const std::string& caminhoArquivo
) {

    std::ifstream arquivo(
        caminhoArquivo
    );


    if (
        !arquivo.is_open()
    ) {

        return
            false;
    }


    std::string linha;


    if (
        !std::getline(
            arquivo,
            linha
        )
    ) {

        throw std::runtime_error(
            "Arquivo CSV de dados vazio."
        );
    }


    const char separador =
        detectarSeparador(
            linha
        );


    double topo =
        0.0;


    int indice =
        0;


    int numeroLinha =
        1;


    while (
        std::getline(
            arquivo,
            linha
        )
    ) {

        ++numeroLinha;


        if (
            linha.empty()
        ) {

            continue;
        }


        std::stringstream ss(
            linha
        );


        std::string profundidadeStr;

        std::string sonicoStr;

        std::string tipoStr;


        std::getline(
            ss,
            profundidadeStr,
            separador
        );


        std::getline(
            ss,
            sonicoStr,
            separador
        );


        std::getline(
            ss,
            tipoStr,
            separador
        );


        profundidadeStr =
            limparTexto(
                profundidadeStr
            );


        sonicoStr =
            limparTexto(
                sonicoStr
            );


        tipoStr =
            limparTexto(
                tipoStr
            );


        // ==================================================
        // PROFUNDIDADE
        // ==================================================

        if (
            profundidadeStr.empty()
        ) {

            throw std::runtime_error(
                "Profundidade ausente na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        double base;


        try {

            base =
                std::stod(
                    profundidadeStr
                );
        }
        catch (...) {

            throw std::runtime_error(
                "Profundidade invalida na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        if (
            base <= topo
        ) {

            throw std::runtime_error(
                "As profundidades devem estar em ordem crescente. "
                "Erro na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        // ==================================================
        // SÔNICO
        // ==================================================

        double deltaT =
            std::numeric_limits<double>::
            quiet_NaN();


        if (
            !sonicoStr.empty()
        ) {

            try {

                deltaT =
                    std::stod(
                        sonicoStr
                    );
            }
            catch (...) {

                throw std::runtime_error(
                    "Valor sonico invalido na linha "
                    +
                    std::to_string(
                        numeroLinha
                    )
                    +
                    "."
                );
            }


            if (
                deltaT <= 0.0
            ) {

                throw std::runtime_error(
                    "O valor sonico deve ser maior que zero. "
                    "Linha "
                    +
                    std::to_string(
                        numeroLinha
                    )
                    +
                    "."
                );
            }
        }


        // ==================================================
        // TIPO DA CAMADA
        // ==================================================

        TipoCamada tipo =
            TipoCamada::DESCONHECIDA;


        if (
            !tipoStr.empty()
        ) {

            tipo =
                Camada::converterTipo(
                    tipoStr
                );
        }
        else if (
            std::isfinite(
                deltaT
            )
        ) {

            tipo =
                TipoCamada::FORMACAO;
        }


        if (
            tipo
            ==
            TipoCamada::DESCONHECIDA
        ) {

            throw std::runtime_error(
                "Tipo de camada ausente ou invalido na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        if (
            tipo
            ==
            TipoCamada::FORMACAO
            &&
            !std::isfinite(
                deltaT
            )
        ) {

            throw std::runtime_error(
                "Camada de formacao sem registro sonico na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        // ==================================================
        // CRIAÇÃO DA CAMADA
        // ==================================================

        poco.adicionarCamada(

            Camada(
                indice,
                topo,
                base,
                deltaT,
                tipo
            )
        );


        topo =
            base;


        ++indice;
    }


    if (
        indice == 0
    ) {

        throw std::runtime_error(
            "Nenhuma camada valida encontrada no CSV."
        );
    }


    poco.calcularProfundidadeMaxima();


    return
        poco.validarDados();
}


// ==========================================================
// CARREGAMENTO DOS PARÂMETROS
// ==========================================================

bool
SimuladorJanelaOperacional::carregarParametrosCSV(
    const std::string& caminhoArquivo
) {

    std::ifstream arquivo(
        caminhoArquivo
    );


    if (
        !arquivo.is_open()
    ) {

        return
            false;
    }


    std::string linha;


    if (
        !std::getline(
            arquivo,
            linha
        )
    ) {

        throw std::runtime_error(
            "Arquivo de parametros vazio."
        );
    }


    const char separador =
        detectarSeparador(
            linha
        );


    int numeroLinha =
        1;


    while (
        std::getline(
            arquivo,
            linha
        )
    ) {

        ++numeroLinha;


        if (
            linha.empty()
        ) {

            continue;
        }


        std::stringstream ss(
            linha
        );


        std::string nome;

        std::string valorStr;


        std::getline(
            ss,
            nome,
            separador
        );


        std::getline(
            ss,
            valorStr,
            separador
        );


        nome =
            normalizarParametro(
                nome
            );


        valorStr =
            limparTexto(
                valorStr
            );


        if (
            nome.empty()
            ||
            valorStr.empty()
        ) {

            throw std::runtime_error(
                "Parametro ou valor ausente na linha "
                +
                std::to_string(
                    numeroLinha
                )
                +
                "."
            );
        }


        double valor;


        try {

            valor =
                std::stod(
                    valorStr
                );
        }
        catch (...) {

            throw std::runtime_error(
                "Valor invalido para o parametro "
                +
                nome
                +
                "."
            );
        }


        // ==================================================
        // PETROFÍSICA
        // ==================================================

        if (
            nome == "densidade_matriz"
        ) {

            parametros.definirDensidadeMatriz(
                valor
            );
        }

        else if (
            nome == "densidade_fluido"
        ) {

            parametros.definirDensidadeFluido(
                valor
            );
        }

        else if (
            nome == "densidade_agua_mar"
        ) {

            parametros.definirDensidadeAguaMar(
                valor
            );
        }

        else if (
            nome == "densidade_sedimento"
        ) {

            parametros.definirDensidadeSedimento(
                valor
            );
        }

        else if (
            nome == "delta_t_matriz"
        ) {

            parametros.definirDeltaTMatriz(
                valor
            );
        }

        else if (
            nome == "delta_t_fluido"
        ) {

            parametros.definirDeltaTFluido(
                valor
            );
        }

        else if (
            nome == "porosidade_sedimento"
        ) {

            parametros.definirPorosidadeSedimento(
                valor
            );
        }

        else if (
            nome == "porosidade_minima"
        ) {

            parametros.definirLimitesPorosidade(

                valor,

                parametros.getPorosidadeMaxima()
            );
        }

        else if (
            nome == "porosidade_maxima"
        ) {

            parametros.definirLimitesPorosidade(

                parametros.getPorosidadeMinima(),

                valor
            );
        }


        // ==================================================
        // GEOPRESSÕES
        // ==================================================

        else if (
            nome == "gradiente_hidrostatico"
        ) {

            parametros.definirGradienteHidrostatico(
                valor
            );
        }

        else if (
            nome == "expoente_eaton"
        ) {

            parametros.definirExpoenteEaton(
                valor
            );
        }

        else if (
            nome == "coeficiente_poisson"
        ) {

            parametros.definirCoeficientePoisson(
                valor
            );
        }

        else if (
            nome == "delta_t_referencia"
        ) {

            parametros.definirDeltaTReferencia(
                valor
            );
        }

        else if (
            nome == "constante_compactacao"
        ) {

            parametros.definirConstanteCompactacao(
                valor
            );
        }


        // ==================================================
        // ECD
        // ==================================================

        else if (
            nome == "densidade_lama"
        ) {

            parametros.definirDensidadeLama(
                valor
            );
        }

        else if (
            nome == "perda_pressao_ecd"
        ) {

            parametros.definirPerdaPressaoECD(
                valor
            );
        }

        else if (
            nome == "profundidade_ecd"
        ) {

            parametros.definirProfundidadeECD(
                valor
            );
        }


        // ==================================================
        // PARÂMETRO DESCONHECIDO
        // ==================================================

        else {

            throw std::runtime_error(
                "Parametro desconhecido: "
                +
                nome
                +
                "."
            );
        }
    }


    if (
        !parametros.validarParametros()
    ) {

        throw std::runtime_error(
            "Os parametros carregados sao fisicamente invalidos."
        );
    }


    return
        true;
}


// ==========================================================
// GETTERS
// ==========================================================

Poco&
SimuladorJanelaOperacional::getPoco() {

    return
        poco;
}


ParametrosSimulacao&
SimuladorJanelaOperacional::getParametros() {

    return
        parametros;
}


Resultados&
SimuladorJanelaOperacional::getResultados() {

    return
        resultados;
}


// ==========================================================
// PETROFÍSICA
// ==========================================================

void
SimuladorJanelaOperacional::
calcularPetrofisica() {

    if (
        !parametros.validarParametros()
    ) {

        throw std::logic_error(
            "Parametros da simulacao invalidos."
        );
    }


    ModeloPetrofisico modelo(
        parametros
    );


    modelo.processarPoco(
        poco
    );
}


// ==========================================================
// GEOPRESSÕES
// ==========================================================

void
SimuladorJanelaOperacional::
calcularGeopressoes() {

    ModeloGeopressoes modelo(
        parametros
    );


    modelo.processarPoco(
        poco
    );
}


// ==========================================================
// FRATURA
// ==========================================================

void
SimuladorJanelaOperacional::
calcularFratura() {

    ModeloFratura modelo(
        parametros
    );


    modelo.processarPoco(
        poco
    );
}


// ==========================================================
// JANELAS
// ==========================================================

void
SimuladorJanelaOperacional::
determinarJanelas() {

    resultados.limparJanelas();


    for (
        const auto& camada :
        poco.getCamadas()
    ) {

        const double gp =
            camada.getGradientePoro();


        const double gf =
            camada.getGradienteFratura();


        if (
            std::isnan(gp)
            ||
            std::isnan(gf)
        ) {

            continue;
        }


        if (
            gf > gp
        ) {

            resultados.adicionarJanela(

                JanelaOperacional(
                    camada.getProfundidadeMedia(),
                    gp,
                    gf
                )
            );
        }
    }
}


// ==========================================================
// ECD
// ==========================================================

void
SimuladorJanelaOperacional::avaliarECD(
    double densidadeLama,
    double perdaPressao,
    double profundidade
) {

    if (
        resultados
            .obterJanelas()
            .empty()
    ) {

        throw std::logic_error(
            "Nenhuma janela operacional disponivel."
        );
    }


    CalculadoraECD calculadora(

        densidadeLama,

        perdaPressao,

        profundidade
    );


    const double ecd =
        calculadora.calcularECD();


    const auto& janelas =
        resultados.obterJanelas();


    const JanelaOperacional*
    janelaMaisProxima =
        &janelas.front();


    double menorDiferenca =
        std::abs(
            janelaMaisProxima
                ->getProfundidade()
            -
            profundidade
        );


    for (
        const auto& janela :
        janelas
    ) {

        const double diferenca =
            std::abs(
                janela.getProfundidade()
                -
                profundidade
            );


        if (
            diferenca
            <
            menorDiferenca
        ) {

            menorDiferenca =
                diferenca;


            janelaMaisProxima =
                &janela;
        }
    }


    const double gp =
        janelaMaisProxima
            ->obterLimiteInferior();


    const double gf =
        janelaMaisProxima
            ->obterLimiteSuperior();


    const std::string classificacao =
        calculadora.avaliarJanela(
            *janelaMaisProxima
        );


    resultados.definirResultadoECD(

        janelaMaisProxima
            ->getProfundidade(),

        densidadeLama,

        perdaPressao,

        ecd,

        gp,

        gf,

        classificacao
    );
}


// ==========================================================
// EXECUÇÃO COMPLETA
// ==========================================================

void
SimuladorJanelaOperacional::
executarSimulacao() {

    calcularPetrofisica();

    calcularGeopressoes();

    calcularFratura();

    determinarJanelas();


    resultados.definirSimulacaoValida(
        true
    );
}


// ==========================================================
// EXPORTAÇÃO
// ==========================================================

bool
SimuladorJanelaOperacional::
exportarResultados(
    const std::string& caminhoArquivo
) const {

    return
        resultados.exportarDados(
            caminhoArquivo
        );
}