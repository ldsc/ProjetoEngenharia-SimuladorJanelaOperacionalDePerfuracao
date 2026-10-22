#ifndef CALCULADORAECD_H
#define CALCULADORAECD_H

#include "JanelaOperacional.h"

#include <string>


class CalculadoraECD {

private:

    double densidadeLama;

    double perdaPressao;

    double profundidade;


public:

    CalculadoraECD();


    CalculadoraECD(
        double densidadeLama,
        double perdaPressao,
        double profundidade
    );


    // ======================================================
    // SETTERS
    // ======================================================

    void definirDensidadeLama(
        double valor
    );


    void definirPerdaPressao(
        double valor
    );


    void definirProfundidade(
        double valor
    );


    // ======================================================
    // GETTERS
    // ======================================================

    double getDensidadeLama() const;


    double getPerdaPressao() const;


    double getProfundidade() const;


    // ======================================================
    // CÁLCULO
    // ======================================================

    bool validarParametros() const;


    double calcularECD() const;


    std::string avaliarJanela(
        const JanelaOperacional& janela
    ) const;
};


#endif