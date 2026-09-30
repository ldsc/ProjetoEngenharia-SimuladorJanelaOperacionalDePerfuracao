#ifndef JANELAOPERACIONAL_H
#define JANELAOPERACIONAL_H

#include <string>


class JanelaOperacional {

private:

    double profundidade;

    double gradientePoro;

    double gradienteFratura;

    double larguraJanela;


public:

    JanelaOperacional();


    JanelaOperacional(
        double profundidade,
        double gradientePoro,
        double gradienteFratura
    );


    // ======================================================
    // JANELA OPERACIONAL
    // ======================================================

    double calcularLargura();


    bool verificarPesoLama(
        double pesoLama
    ) const;


    std::string classificarPesoLama(
        double pesoLama
    ) const;


    // ======================================================
    // GETTERS
    // ======================================================

    double obterLimiteInferior() const;


    double obterLimiteSuperior() const;


    double getProfundidade() const;


    double getLarguraJanela() const;
};


#endif