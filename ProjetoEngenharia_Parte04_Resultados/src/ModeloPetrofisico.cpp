#include "ModeloPetrofisico.h"

#include <algorithm>
#include <stdexcept>


ModeloPetrofisico::ModeloPetrofisico(
    const ParametrosSimulacao& parametros
)
    : parametros(&parametros)
{
}


// ==========================================================
// POROSIDADE DE WYLLIE
// ==========================================================

double ModeloPetrofisico::calcularPorosidade(
    double deltaT
) const {

    const double denominador =
        parametros->getDeltaTFluido()
        -
        parametros->getDeltaTMatriz();


    if (
        denominador <= 0.0
    ) {

        throw std::runtime_error(
            "Parametros de Wyllie invalidos."
        );
    }


    const double phiCalculada =
        (
            deltaT
            -
            parametros->getDeltaTMatriz()
        )
        /
        denominador;


    return
        std::clamp(

            phiCalculada,

            parametros->getPorosidadeMinima(),

            parametros->getPorosidadeMaxima()
        );
}


// ==========================================================
// DENSIDADE BULK
// ==========================================================

double ModeloPetrofisico::calcularDensidadeBulk(
    double porosidade
) const {

    return

        (
            1.0
            -
            porosidade
        )
        *
        parametros->getDensidadeMatriz()

        +

        porosidade
        *
        parametros->getDensidadeFluido();
}


// ==========================================================
// FORMAÇÃO COM REGISTRO SÔNICO
// ==========================================================

void ModeloPetrofisico::processarCamada(
    Camada& camada
) const {

    if (
        !camada.possuiDeltaT()
    ) {

        throw std::runtime_error(
            "Camada de formacao sem registro sonico."
        );
    }


    const double porosidade =
        calcularPorosidade(
            camada.getDeltaT()
        );


    const double densidadeBulk =
        calcularDensidadeBulk(
            porosidade
        );


    camada.definirPorosidade(
        porosidade
    );


    camada.definirDensidadeBulk(
        densidadeBulk
    );
}


// ==========================================================
// PROCESSAMENTO DO POÇO
// ==========================================================

void ModeloPetrofisico::processarPoco(
    Poco& poco
) const {

    auto& camadas =
        poco.getCamadas();


    for (
        auto& camada :
        camadas
    ) {

        switch (
            camada.getTipo()
        ) {

            // ==============================================
            // ÁGUA
            // ==============================================

            case TipoCamada::AGUA:

                camada.definirPorosidade(
                    1.0
                );


                camada.definirDensidadeBulk(
                    parametros
                        ->getDensidadeAguaMar()
                );

                break;


            // ==============================================
            // SEDIMENTO INCONSOLIDADO
            // ==============================================

            case TipoCamada::SEDIMENTO:

                camada.definirPorosidade(
                    parametros
                        ->getPorosidadeSedimento()
                );


                camada.definirDensidadeBulk(
                    parametros
                        ->getDensidadeSedimento()
                );

                break;


            // ==============================================
            // FORMAÇÃO CONSOLIDADA
            // ==============================================

            case TipoCamada::FORMACAO:

                processarCamada(
                    camada
                );

                break;


            // ==============================================
            // AR
            // ==============================================

            case TipoCamada::AR:

                camada.definirPorosidade(
                    1.0
                );


                camada.definirDensidadeBulk(
                    0.0
                );

                break;


            // ==============================================
            // TIPO INVÁLIDO
            // ==============================================

            default:

                throw std::runtime_error(
                    "Tipo de camada desconhecido."
                );
        }
    }
}