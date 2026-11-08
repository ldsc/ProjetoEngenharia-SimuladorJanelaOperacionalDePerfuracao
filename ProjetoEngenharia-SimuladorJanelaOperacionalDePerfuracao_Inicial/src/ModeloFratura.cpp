#include "ModeloFratura.h"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace {

constexpr double FT_PER_M = 3.28084;
constexpr double PSI_FT_PER_LB_GAL = 0.052;

}


ModeloFratura::ModeloFratura(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros)
{
}


// ==========================================================
// TENSÃO HORIZONTAL MÍNIMA
//
// Shmin = [nu / (1 - nu)] * (sigmaV - Pp) + Pp
// ==========================================================

double ModeloFratura::calcularTensaoHorizontalMinima(
    const Camada& camada
) const {

    const double sigmaV =
        camada.getTensaoSobrecarga();

    const double pressaoPoro =
        camada.getPressaoPoro();

    const double nu =
        parametros->getCoeficientePoisson();


    if (
        std::isnan(pressaoPoro)
    ) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    if (
        nu <= 0.0 ||
        nu >= 0.5
    ) {

        throw std::runtime_error(
            "Coeficiente de Poisson invalido."
        );
    }


    const double tensaoEfetivaVertical =
        sigmaV
        - pressaoPoro;


    const double shmin =
        (
            nu
            /
            (1.0 - nu)
        )
        *
        tensaoEfetivaVertical
        +
        pressaoPoro;


    return shmin;
}


// ==========================================================
// GRADIENTE DE FRATURA
//
// Gf(psi/ft) = Shmin / H(ft)
//
// Gf(lb/gal) = Gf(psi/ft) / 0.052
// ==========================================================

double ModeloFratura::calcularGradienteFratura(
    const Camada& camada
) const {

    const double shmin =
        camada.getTensaoHorizontalMinima();


    if (
        std::isnan(shmin)
    ) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    const double profundidadeFt =
        camada.getBase()
        * FT_PER_M;


    if (
        profundidadeFt <= 0.0
    ) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    const double gradientePsiFt =
        shmin
        / profundidadeFt;


    const double gradientePpg =
        gradientePsiFt
        / PSI_FT_PER_LB_GAL;


    return gradientePpg;
}


// ==========================================================
// PROCESSAMENTO COMPLETO DO POÇO
// ==========================================================

void ModeloFratura::processarPoco(
    Poco& poco
) const {

    auto& camadas =
        poco.getCamadas();


    for (
        auto& camada : camadas
    ) {

        if (
            std::isnan(
                camada.getPressaoPoro()
            )
        ) {

            const double nan =
                std::numeric_limits<double>::quiet_NaN();


            camada.definirTensaoHorizontalMinima(
                nan
            );


            camada.definirGradienteFratura(
                nan
            );


            continue;
        }


        const double shmin =
            calcularTensaoHorizontalMinima(
                camada
            );


        camada.definirTensaoHorizontalMinima(
            shmin
        );


        const double gradienteFratura =
            calcularGradienteFratura(
                camada
            );


        camada.definirGradienteFratura(
            gradienteFratura
        );
    }
}