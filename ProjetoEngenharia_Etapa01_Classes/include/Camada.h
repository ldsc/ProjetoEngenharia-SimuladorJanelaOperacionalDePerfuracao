#ifndef CAMADA_H
#define CAMADA_H

#include <string>


enum class TipoCamada {

    AGUA,

    SEDIMENTO,

    FORMACAO,

    AR,

    DESCONHECIDA
};


class Camada {

private:

    int indice;

    double topo;

    double base;

    double profundidadeMedia;

    double deltaT;

    TipoCamada tipo;


    // Resultados calculados

    double porosidade;

    double densidadeBulk;

    double tensaoSobrecarga;

    double pressaoPoro;

    double gradientePoro;

    double tensaoHorizontalMinima;

    double gradienteFratura;


public:

    Camada();


    Camada(
        int indice,
        double topo,
        double base,
        double deltaT,
        TipoCamada tipo = TipoCamada::FORMACAO
    );


    // ======================================================
    // DADOS GEOMÉTRICOS
    // ======================================================

    int getIndice() const;

    double getTopo() const;

    double getBase() const;

    double getProfundidadeMedia() const;


    // ======================================================
    // PERFIL SÔNICO
    // ======================================================

    double getDeltaT() const;

    bool possuiDeltaT() const;


    // ======================================================
    // TIPO DA CAMADA
    // ======================================================

    TipoCamada getTipo() const;

    void definirTipo(
        TipoCamada novoTipo
    );


    std::string getTipoTexto() const;


    static TipoCamada converterTipo(
        const std::string& texto
    );


    // ======================================================
    // PETROFÍSICA
    // ======================================================

    void definirPorosidade(
        double valor
    );

    double getPorosidade() const;


    void definirDensidadeBulk(
        double valor
    );

    double getDensidadeBulk() const;


    // ======================================================
    // GEOPRESSÕES
    // ======================================================

    void definirSobrecarga(
        double valor
    );

    double getTensaoSobrecarga() const;


    void definirPressaoPoro(
        double valor
    );

    double getPressaoPoro() const;


    void definirGradientePoro(
        double valor
    );

    double getGradientePoro() const;


    // ======================================================
    // FRATURA
    // ======================================================

    void definirTensaoHorizontalMinima(
        double valor
    );

    double getTensaoHorizontalMinima() const;


    void definirGradienteFratura(
        double valor
    );

    double getGradienteFratura() const;
};


#endif