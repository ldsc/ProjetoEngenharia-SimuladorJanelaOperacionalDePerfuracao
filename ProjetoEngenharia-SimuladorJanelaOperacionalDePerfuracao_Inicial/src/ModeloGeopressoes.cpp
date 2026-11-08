#include "ModeloGeopressoes.h"

#include <cmath>
#include <limits>
#include <stdexcept>


namespace {

constexpr double FT_PER_M = 3.28084;
constexpr double PSI_FT_PER_LB_GAL = 0.052;
constexpr double CONV_DENSITY = 8.345;

}


ModeloGeopressoes::ModeloGeopressoes(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros)
{
}


// ==========================================================
// TENDÊNCIA NORMAL DO PERFIL SÔNICO
// Δtn = Δt0 * exp(-k * z)
// profundidade recebida em metros
// ==========================================================

double ModeloGeopressoes::calcularTendenciaNormal(
    double profundidade
) const {

    if (profundidade < 0.0) {
        throw std::invalid_argument(
            "Profundidade invalida para tendencia normal."
        );
    }

    const double profundidadeFt =
        profundidade * FT_PER_M;

    return
        parametros->getDeltaTReferencia()
        *
        std::exp(
            -parametros->getConstanteCompactacao()
            * profundidadeFt
        );
}


// ==========================================================
// PRESSÃO NORMAL HIDROSTÁTICA
// Pn = GradNormal * H(ft)
// ==========================================================

double ModeloGeopressoes::calcularPressaoNormal(
    double profundidade
) const {

    if (profundidade < 0.0) {
        throw std::invalid_argument(
            "Profundidade invalida para pressao normal."
        );
    }

    const double profundidadeFt =
        profundidade * FT_PER_M;

    return
        parametros->getGradienteHidrostaticoNormal()
        * profundidadeFt;
}


// ==========================================================
// PRESSÃO DE PORO - MÉTODO DE EATON
//
// Pp = σv - (σv - Pn) * (Δtn / Δt)^alpha
// ==========================================================

double ModeloGeopressoes::calcularPressaoPoro(
    const Camada& camada
) const {

    if (!camada.possuiDeltaT()) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    const double profundidade =
        camada.getBase();


    const double deltaTNormal =
        calcularTendenciaNormal(
            profundidade
        );


    const double pressaoNormal =
        calcularPressaoNormal(
            profundidade
        );


    const double deltaTObservado =
        camada.getDeltaT();


    if (deltaTObservado <= 0.0) {

        throw std::runtime_error(
            "Valor de deltaT invalido."
        );
    }


    const double razao =
        deltaTNormal
        / deltaTObservado;


    const double sigmaV =
        camada.getTensaoSobrecarga();


    const double pressaoPoro =
        sigmaV
        -
        (
            sigmaV
            - pressaoNormal
        )
        *
        std::pow(
            razao,
            parametros->getExpoenteEaton()
        );


    return pressaoPoro;
}


// ==========================================================
// GRADIENTE DE PRESSÃO DE PORO
//
// Gp(psi/ft) = Pp / H
//
// Gp(lb/gal) = Gp(psi/ft) / 0.052
// ==========================================================

double ModeloGeopressoes::calcularGradientePoro(
    const Camada& camada
) const {

    if (
        std::isnan(
            camada.getPressaoPoro()
        )
    ) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    const double profundidadeFt =
        camada.getBase()
        * FT_PER_M;


    if (profundidadeFt <= 0.0) {

        return
            std::numeric_limits<double>::quiet_NaN();
    }


    const double gradientePsiFt =
        camada.getPressaoPoro()
        / profundidadeFt;


    const double gradientePpg =
        gradientePsiFt
        / PSI_FT_PER_LB_GAL;


    return gradientePpg;
}


// ==========================================================
// TENSÃO DE SOBRECARGA
//
// Δσv = 0.052 * rho(lb/gal) * ΔH(ft)
//
// σv = soma acumulada
// ==========================================================

void ModeloGeopressoes::calcularSobrecarga(
    Poco& poco
) const {

    auto& camadas =
        poco.getCamadas();


    double sigmaAcumulada = 0.0;


    for (
        auto& camada : camadas
    ) {

        const double espessuraMetros =
            camada.getBase()
            - camada.getTopo();


        const double espessuraFt =
            espessuraMetros
            * FT_PER_M;


        const double densidadeLbGal =
            camada.getDensidadeBulk()
            * CONV_DENSITY;


        const double incrementoSigma =
            PSI_FT_PER_LB_GAL
            *
            densidadeLbGal
            *
            espessuraFt;


        sigmaAcumulada +=
            incrementoSigma;


        camada.definirSobrecarga(
            sigmaAcumulada
        );
    }
}


// ==========================================================
// PROCESSAMENTO COMPLETO DO POÇO
// ==========================================================

void ModeloGeopressoes::processarPoco(
    Poco& poco
) const {

    calcularSobrecarga(
        poco
    );


    auto& camadas =
        poco.getCamadas();


    for (
        auto& camada : camadas
    ) {

        if (
            !camada.possuiDeltaT()
        ) {

            const double nan =
                std::numeric_limits<double>::quiet_NaN();


            camada.definirPressaoPoro(
                nan
            );


            camada.definirGradientePoro(
                nan
            );


            continue;
        }


        const double pressaoPoro =
            calcularPressaoPoro(
                camada
            );


        camada.definirPressaoPoro(
            pressaoPoro
        );


        const double gradientePoro =
            calcularGradientePoro(
                camada
            );


        camada.definirGradientePoro(
            gradientePoro
        );
    }
}