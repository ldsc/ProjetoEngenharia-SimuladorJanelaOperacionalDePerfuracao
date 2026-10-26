#ifndef SIMULADOR_JANELA_OPERACIONAL_H
#define SIMULADOR_JANELA_OPERACIONAL_H

#include "CalculadoraECD.h"
#include "JanelaOperacional.h"
#include "ModeloFratura.h"
#include "ModeloGeopressoes.h"
#include "ModeloPetrofisico.h"
#include "ParametrosSimulacao.h"
#include "Poco.h"
#include "Resultados.h"

#include <string>


class SimuladorJanelaOperacional {

private:

    Poco poco;

    ParametrosSimulacao parametros;

    Resultados resultados;


public:

    // ======================================================
    // CONSTRUTOR
    // ======================================================

    SimuladorJanelaOperacional();


    // ======================================================
    // ENTRADA DE DADOS
    // ======================================================

    bool carregarDadosCSV(
        const std::string& caminhoArquivo
    );


    bool carregarParametrosCSV(
        const std::string& caminhoArquivo
    );


    // ======================================================
    // GETTERS
    // ======================================================

    Poco& getPoco();


    ParametrosSimulacao&
    getParametros();


    Resultados&
    getResultados();


    // ======================================================
    // PETROFÍSICA
    // ======================================================

    void calcularPetrofisica();


    // ======================================================
    // GEOPRESSÕES
    // ======================================================

    void calcularGeopressoes();


    // ======================================================
    // FRATURA
    // ======================================================

    void calcularFratura();


    // ======================================================
    // JANELA OPERACIONAL
    // ======================================================

    void determinarJanelas();


    // ======================================================
    // ECD
    // ======================================================

    void avaliarECD(
        double densidadeLama,
        double perdaPressao,
        double profundidade
    );


    // ======================================================
    // EXECUÇÃO COMPLETA
    // ======================================================

    void executarSimulacao();


    // ======================================================
    // EXPORTAÇÃO
    // ======================================================

    bool exportarResultados(
        const std::string& caminhoArquivo
    ) const;
};


#endif