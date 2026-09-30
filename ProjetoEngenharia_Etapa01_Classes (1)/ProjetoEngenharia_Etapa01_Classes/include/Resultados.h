#ifndef RESULTADOS_H
#define RESULTADOS_H

#include "JanelaOperacional.h"
#include "ParametrosSimulacao.h"
#include "Poco.h"

#include <string>
#include <vector>


class Resultados {

private:

    std::vector<JanelaOperacional> janelas;


    bool simulacaoValida;


    // ======================================================
    // RESULTADO DA ECD
    // ======================================================

    bool possuiECD;

    double profundidadeECD;

    double densidadeLamaECD;

    double perdaPressaoECD;

    double ecdCalculada;

    double gradientePoroECD;

    double gradienteFraturaECD;

    std::string classificacaoECD;


public:

    Resultados();


    // ======================================================
    // JANELAS OPERACIONAIS
    // ======================================================

    void adicionarJanela(
        const JanelaOperacional& janela
    );


    void limparJanelas();


    const std::vector<JanelaOperacional>&
    obterJanelas() const;


    // ======================================================
    // CONTROLE DA SIMULAÇÃO
    // ======================================================

    void definirSimulacaoValida(
        bool valor
    );


    bool getSimulacaoValida() const;


    // ======================================================
    // RESULTADO DA ECD
    // ======================================================

    void definirResultadoECD(
        double profundidade,
        double densidadeLama,
        double perdaPressao,
        double ecd,
        double gp,
        double gf,
        const std::string& classificacao
    );


    bool temResultadoECD() const;


    double getProfundidadeECD() const;


    double getDensidadeLamaECD() const;


    double getPerdaPressaoECD() const;


    double getECDCalculada() const;


    double getGradientePoroECD() const;


    double getGradienteFraturaECD() const;


    const std::string&
    getClassificacaoECD() const;


    // ======================================================
    // EXPORTAÇÃO
    // ======================================================

    bool exportarDados(
        const std::string& caminhoArquivo
    ) const;


    bool exportarResultadoECD(
        const std::string& caminhoArquivo
    ) const;


    bool exportarDadosCompletos(
        const Poco& poco,
        const ParametrosSimulacao& parametros,
        const std::string& caminhoArquivo
    ) const;


    // ======================================================
    // GRÁFICOS
    // ======================================================

    bool gerarGraficos(
        const Poco& poco,
        const ParametrosSimulacao& parametros,
        const std::string& diretorioSaida
    ) const;
};


#endif