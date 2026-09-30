// Etapa 1: estrutura de classes; metodos pendentes lancam logic_error.
#include "Camada.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>
#include <string>
#include <stdexcept>

Camada::Camada()
    : indice(0),
      topo(0.0),
      base(0.0),
      profundidadeMedia(0.0),
      deltaT(
          std::numeric_limits<double>::quiet_NaN()
      ),
      tipo(
          TipoCamada::DESCONHECIDA
      ),
      porosidade(
          std::numeric_limits<double>::quiet_NaN()
      ),
      densidadeBulk(
          std::numeric_limits<double>::quiet_NaN()
      ),
      tensaoSobrecarga(
          std::numeric_limits<double>::quiet_NaN()
      ),
      pressaoPoro(
          std::numeric_limits<double>::quiet_NaN()
      ),
      gradientePoro(
          std::numeric_limits<double>::quiet_NaN()
      ),
      tensaoHorizontalMinima(
          std::numeric_limits<double>::quiet_NaN()
      ),
      gradienteFratura(
          std::numeric_limits<double>::quiet_NaN()
      ) {
}

Camada::Camada(
    int indice,
    double topo,
    double base,
    double deltaT,
    TipoCamada tipo
)
    : indice(indice),
      topo(topo),
      base(base),
      profundidadeMedia(
          0.5
          *
          (
              topo
              +
              base
          )
      ),
      deltaT(deltaT),
      tipo(tipo),
      porosidade(
          std::numeric_limits<double>::quiet_NaN()
      ),
      densidadeBulk(
          std::numeric_limits<double>::quiet_NaN()
      ),
      tensaoSobrecarga(
          std::numeric_limits<double>::quiet_NaN()
      ),
      pressaoPoro(
          std::numeric_limits<double>::quiet_NaN()
      ),
      gradientePoro(
          std::numeric_limits<double>::quiet_NaN()
      ),
      tensaoHorizontalMinima(
          std::numeric_limits<double>::quiet_NaN()
      ),
      gradienteFratura(
          std::numeric_limits<double>::quiet_NaN()
      ) {
}

// ==========================================================
// DADOS GEOMÉTRICOS
// ==========================================================

int Camada::getIndice() const {

    return indice;
}

double Camada::getTopo() const {

    return topo;
}

double Camada::getBase() const {

    return base;
}

double Camada::getProfundidadeMedia() const {

    return profundidadeMedia;
}

// ==========================================================
// PERFIL SÔNICO
// ==========================================================

double Camada::getDeltaT() const {

    return deltaT;
}

bool Camada::possuiDeltaT() const {

    return
        std::isfinite(deltaT);
}

// ==========================================================
// TIPO DA CAMADA
// ==========================================================

TipoCamada Camada::getTipo() const {

    return tipo;
}

void Camada::definirTipo(
    TipoCamada novoTipo
) {

    tipo =
        novoTipo;
}

std::string Camada::getTipoTexto() const {

    switch (
        tipo
    ) {

        case TipoCamada::AGUA:

            return "AGUA";


        case TipoCamada::SEDIMENTO:

            return "SEDIMENTO";


        case TipoCamada::FORMACAO:

            return "FORMACAO";


        case TipoCamada::AR:

            return "AR";


        default:

            return "DESCONHECIDA";
    }
}

// ==========================================================
// CONVERSÃO TEXTO -> ENUM
// ==========================================================

TipoCamada Camada::converterTipo(
    const std::string& texto
) {

    std::string valor =
        texto;


    // Remove espaços

    valor.erase(

        std::remove_if(

            valor.begin(),

            valor.end(),

            [](unsigned char caractere) {

                return
                    std::isspace(
                        caractere
                    );
            }

        ),

        valor.end()
    );


    // Converte para maiúsculo

    std::transform(

        valor.begin(),

        valor.end(),

        valor.begin(),

        [](unsigned char caractere) {

            return
                static_cast<char>(
                    std::toupper(
                        caractere
                    )
                );
        }
    );


    if (
        valor == "AGUA"
    ) {

        return
            TipoCamada::AGUA;
    }


    if (
        valor == "SEDIMENTO"
        ||
        valor == "SEDIMENTOS"
    ) {

        return
            TipoCamada::SEDIMENTO;
    }


    if (
        valor == "FORMACAO"
        ||
        valor == "FORMACAO_ROCHOSA"
    ) {

        return
            TipoCamada::FORMACAO;
    }


    if (
        valor == "AR"
    ) {

        return
            TipoCamada::AR;
    }


    return
        TipoCamada::DESCONHECIDA;
}

// ==========================================================
// PETROFÍSICA
// ==========================================================

void Camada::definirPorosidade(
    double valor
) {

    porosidade =
        valor;
}

double Camada::getPorosidade() const {

    return porosidade;
}

void Camada::definirDensidadeBulk(
    double valor
) {

    densidadeBulk =
        valor;
}

double Camada::getDensidadeBulk() const {

    return densidadeBulk;
}

// ==========================================================
// GEOPRESSÕES
// ==========================================================

void Camada::definirSobrecarga(
    double valor
) {

    tensaoSobrecarga =
        valor;
}

double Camada::getTensaoSobrecarga() const {

    return tensaoSobrecarga;
}

void Camada::definirPressaoPoro(
    double valor
) {

    pressaoPoro =
        valor;
}

double Camada::getPressaoPoro() const {

    return pressaoPoro;
}

void Camada::definirGradientePoro(
    double valor
) {

    gradientePoro =
        valor;
}

double Camada::getGradientePoro() const {

    return gradientePoro;
}

// ==========================================================
// FRATURA
// ==========================================================

void Camada::definirTensaoHorizontalMinima(
    double valor
) {

    tensaoHorizontalMinima =
        valor;
}

double Camada::getTensaoHorizontalMinima() const {

    return tensaoHorizontalMinima;
}

void Camada::definirGradienteFratura(
    double valor
) {

    gradienteFratura =
        valor;
}

double Camada::getGradienteFratura() const {

    return gradienteFratura;
}
