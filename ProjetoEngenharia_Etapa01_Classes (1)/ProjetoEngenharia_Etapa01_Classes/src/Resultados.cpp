// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "Resultados.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>

// ==========================================================
// CONSTRUTOR
// ==========================================================

Resultados::Resultados()
    : simulacaoValida(false),
      possuiECD(false),
      profundidadeECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      densidadeLamaECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      perdaPressaoECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      ecdCalculada(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      gradientePoroECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      gradienteFraturaECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      classificacaoECD("") {
}

// ==========================================================
// JANELAS OPERACIONAIS
// ==========================================================

void Resultados::adicionarJanela(
    const JanelaOperacional& janela
) {

    janelas.push_back(
        janela
    );
}

void Resultados::limparJanelas() {

    janelas.clear();
}

const std::vector<JanelaOperacional>&
Resultados::obterJanelas() const {

    return
        janelas;
}

// ==========================================================
// SIMULAÇÃO
// ==========================================================

void Resultados::definirSimulacaoValida(
    bool valor
) {

    simulacaoValida =
        valor;
}

bool Resultados::getSimulacaoValida() const {

    return
        simulacaoValida;
}

// ==========================================================
// RESULTADO DA ECD
// ==========================================================

void Resultados::definirResultadoECD(
    double profundidade,
    double densidadeLama,
    double perdaPressao,
    double ecd,
    double gp,
    double gf,
    const std::string& classificacao
) {

    profundidadeECD =
        profundidade;


    densidadeLamaECD =
        densidadeLama;


    perdaPressaoECD =
        perdaPressao;


    ecdCalculada =
        ecd;


    gradientePoroECD =
        gp;


    gradienteFraturaECD =
        gf;


    classificacaoECD =
        classificacao;


    possuiECD =
        true;
}

bool Resultados::temResultadoECD() const {

    return
        possuiECD;
}

double Resultados::getProfundidadeECD() const {

    return
        profundidadeECD;
}

double Resultados::getDensidadeLamaECD() const {

    return
        densidadeLamaECD;
}

double Resultados::getPerdaPressaoECD() const {

    return
        perdaPressaoECD;
}

double Resultados::getECDCalculada() const {

    return
        ecdCalculada;
}

double Resultados::getGradientePoroECD() const {

    return
        gradientePoroECD;
}

double Resultados::getGradienteFraturaECD() const {

    return
        gradienteFraturaECD;
}

const std::string&
Resultados::getClassificacaoECD() const {

    return
        classificacaoECD;
}

// ==========================================================
// EXPORTAÇÃO DAS JANELAS
// ==========================================================

bool Resultados::exportarDados(
    const std::string& caminhoArquivo
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: Resultados::exportarDados ainda nao implementado.");
}

// ==========================================================
// EXPORTAÇÃO DO RESULTADO ECD
// ==========================================================

bool Resultados::exportarResultadoECD(
    const std::string& caminhoArquivo
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: Resultados::exportarResultadoECD ainda nao implementado.");
}

// ==========================================================
// EXPORTAÇÃO COMPLETA DOS DADOS
// ==========================================================

bool Resultados::exportarDadosCompletos(
    const Poco& poco,
    const ParametrosSimulacao& parametros,
    const std::string& caminhoArquivo
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: Resultados::exportarDadosCompletos ainda nao implementado.");
}

// ==========================================================
// GERAÇÃO DOS GRÁFICOS
// ==========================================================

bool Resultados::gerarGraficos(
    const Poco& poco,
    const ParametrosSimulacao& parametros,
    const std::string& diretorioSaida
) const {
    // TODO: implementar na etapa de calculos e integracao.
    throw std::logic_error("Etapa 1: Resultados::gerarGraficos ainda nao implementado.");
}
