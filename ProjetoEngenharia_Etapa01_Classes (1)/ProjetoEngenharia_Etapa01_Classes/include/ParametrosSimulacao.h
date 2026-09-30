#ifndef PARAMETROSSIMULACAO_H
#define PARAMETROSSIMULACAO_H


class ParametrosSimulacao {

private:

    // ======================================================
    // PETROFÍSICA
    // ======================================================

    double densidadeMatriz;

    double densidadeFluido;

    double densidadeAguaMar;

    double densidadeSedimento;


    double deltaTMatriz;

    double deltaTFluido;


    double porosidadeSedimento;

    double porosidadeMinima;

    double porosidadeMaxima;


    // ======================================================
    // GEOPRESSÕES / GEOMECÂNICA
    // ======================================================

    double gradienteHidrostaticoNormal;

    double expoenteEaton;

    double coeficientePoisson;

    double deltaTReferencia;

    double constanteCompactacao;


    // ======================================================
    // PARÂMETROS OPERACIONAIS DA ECD
    // ======================================================

    double densidadeLama;

    double perdaPressaoECD;

    double profundidadeECD;


public:

    // ======================================================
    // CONSTRUTOR
    // ======================================================

    ParametrosSimulacao();


    // ======================================================
    // VALIDAÇÃO
    // ======================================================

    bool validarParametros() const;


    // ======================================================
    // SETTERS - PETROFÍSICA
    // ======================================================

    void definirDensidadeMatriz(
        double valor
    );


    void definirDensidadeFluido(
        double valor
    );


    void definirDensidadeAguaMar(
        double valor
    );


    void definirDensidadeSedimento(
        double valor
    );


    void definirDeltaTMatriz(
        double valor
    );


    void definirDeltaTFluido(
        double valor
    );


    void definirPorosidadeSedimento(
        double valor
    );


    void definirLimitesPorosidade(
        double minimo,
        double maximo
    );


    // ======================================================
    // SETTERS - GEOPRESSÕES
    // ======================================================

    void definirGradienteHidrostatico(
        double valor
    );


    void definirExpoenteEaton(
        double valor
    );


    void definirCoeficientePoisson(
        double valor
    );


    void definirDeltaTReferencia(
        double valor
    );


    void definirConstanteCompactacao(
        double valor
    );


    // ======================================================
    // SETTERS - ECD
    // ======================================================

    void definirDensidadeLama(
        double valor
    );


    void definirPerdaPressaoECD(
        double valor
    );


    void definirProfundidadeECD(
        double valor
    );


    // ======================================================
    // GETTERS - PETROFÍSICA
    // ======================================================

    double getDensidadeMatriz() const;


    double getDensidadeFluido() const;


    double getDensidadeAguaMar() const;


    double getDensidadeSedimento() const;


    double getDeltaTMatriz() const;


    double getDeltaTFluido() const;


    double getPorosidadeSedimento() const;


    double getPorosidadeMinima() const;


    double getPorosidadeMaxima() const;


    // ======================================================
    // GETTERS - GEOPRESSÕES
    // ======================================================

    double getGradienteHidrostaticoNormal() const;


    double getExpoenteEaton() const;


    double getCoeficientePoisson() const;


    double getDeltaTReferencia() const;


    double getConstanteCompactacao() const;


    // ======================================================
    // GETTERS - ECD
    // ======================================================

    double getDensidadeLama() const;


    double getPerdaPressaoECD() const;


    double getProfundidadeECD() const;
};


#endif