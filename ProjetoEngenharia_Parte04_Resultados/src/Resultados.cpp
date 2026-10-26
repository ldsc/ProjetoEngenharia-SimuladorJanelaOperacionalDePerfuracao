#include "Resultados.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>


namespace {

constexpr double FT_PER_M = 3.28084;

constexpr double PSI_FT_PER_LB_GAL = 0.052;

constexpr double CONV_DENSITY = 8.345;


// ==========================================================
// ESTRUTURA AUXILIAR PARA DESENHO DO ENVELOPE
// ==========================================================

struct PontoEnvelope {

    double profundidade;

    double gp;

    double gf;

    double gradienteSobrecarga;
};


// ==========================================================
// ESCREVE NÚMERO OU NaN
// ==========================================================

void escreverNumero(
    std::ostream& arquivo,
    double valor
) {

    if (
        std::isnan(valor)
    ) {

        arquivo << "NaN";
    }
    else {

        arquivo
            << std::fixed
            << std::setprecision(6)
            << valor;
    }
}


// ==========================================================
// VERIFICA SE UM VALOR É VÁLIDO
// ==========================================================

bool valorValido(
    double valor
) {

    return
        !std::isnan(valor)
        &&
        std::isfinite(valor);
}


// ==========================================================
// TENDÊNCIA NORMAL DO PERFIL SÔNICO
// ==========================================================

double calcularDeltaTNormal(
    const Camada& camada,
    const ParametrosSimulacao& parametros
) {

    const double profundidadeFt =
        camada.getBase()
        *
        FT_PER_M;


    return
        parametros.getDeltaTReferencia()
        *
        std::exp(
            -parametros.getConstanteCompactacao()
            *
            profundidadeFt
        );
}


// ==========================================================
// POROSIDADE NORMAL - ATHY
// ==========================================================

double calcularPorosidadeNormal(
    const Camada& camada
) {

    constexpr double PHI0 =
        0.60;

    constexpr double C =
        0.00045;


    double phiNormal =
        PHI0
        *
        std::exp(
            -C
            *
            camada.getProfundidadeMedia()
        );


    phiNormal =
        std::clamp(
            phiNormal,
            0.05,
            0.45
        );


    return
        phiNormal;
}


// ==========================================================
// GRADIENTE DE SOBRECARGA EM PSI/FT
// ==========================================================

double calcularGradienteSobrecargaPsiFt(
    const Camada& camada
) {

    const double profundidadeFt =
        camada.getBase()
        *
        FT_PER_M;


    if (
        profundidadeFt <= 0.0
    ) {

        return
            std::numeric_limits<double>::
            quiet_NaN();
    }


    return
        camada.getTensaoSobrecarga()
        /
        profundidadeFt;
}


// ==========================================================
// GRADIENTE DE SOBRECARGA EM LB/GAL
// ==========================================================

double calcularGradienteSobrecargaPpg(
    const Camada& camada
) {

    const double gradientePsiFt =
        calcularGradienteSobrecargaPsiFt(
            camada
        );


    if (
        !valorValido(
            gradientePsiFt
        )
    ) {

        return
            std::numeric_limits<double>::
            quiet_NaN();
    }


    return
        gradientePsiFt
        /
        PSI_FT_PER_LB_GAL;
}


// ==========================================================
// ESCREVE POLÍGONO NO GNUPLOT
// ==========================================================

void escreverPoligono(
    std::ofstream& script,
    int id,
    double x1,
    double y1,
    double x2,
    double y2,
    double x3,
    double y3,
    double x4,
    double y4,
    const std::string& cor,
    double transparencia
) {

    script
        << "set object "
        << id

        << " polygon from "
        << x1 << "," << y1

        << " to "
        << x2 << "," << y2

        << " to "
        << x3 << "," << y3

        << " to "
        << x4 << "," << y4

        << " to "
        << x1 << "," << y1

        << " fc rgb '"
        << cor
        << "'"

        << " fs transparent solid "
        << transparencia

        << " noborder behind\n";
}

}


// ==========================================================
// CONSTRUTOR
// ==========================================================

Resultados::Resultados()
    : simulacaoValida(false),
      possuiECD(false),
      profundidadeECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      densidadeLamaECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      perdaPressaoECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      ecdCalculada(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      gradientePoroECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      gradienteFraturaECD(
          std::numeric_limits<double>::
          quiet_NaN()
      ),
      classificacaoECD("")
{
}


// ==========================================================
// JANELAS OPERACIONAIS
// ==========================================================

void Resultados::adicionarJanela(
    const JanelaOperacional& janela
) {

    janelas.push_back(
        janela
    );
}


void Resultados::limparJanelas() {

    janelas.clear();
}


const std::vector<JanelaOperacional>&
Resultados::obterJanelas() const {

    return
        janelas;
}


// ==========================================================
// SIMULAÇÃO
// ==========================================================

void Resultados::definirSimulacaoValida(
    bool valor
) {

    simulacaoValida =
        valor;
}


bool Resultados::getSimulacaoValida() const {

    return
        simulacaoValida;
}


// ==========================================================
// RESULTADO DA ECD
// ==========================================================

void Resultados::definirResultadoECD(
    double profundidade,
    double densidadeLama,
    double perdaPressao,
    double ecd,
    double gp,
    double gf,
    const std::string& classificacao
) {

    profundidadeECD =
        profundidade;


    densidadeLamaECD =
        densidadeLama;


    perdaPressaoECD =
        perdaPressao;


    ecdCalculada =
        ecd;


    gradientePoroECD =
        gp;


    gradienteFraturaECD =
        gf;


    classificacaoECD =
        classificacao;


    possuiECD =
        true;
}


bool Resultados::temResultadoECD() const {

    return
        possuiECD;
}


double Resultados::getProfundidadeECD() const {

    return
        profundidadeECD;
}


double Resultados::getDensidadeLamaECD() const {

    return
        densidadeLamaECD;
}


double Resultados::getPerdaPressaoECD() const {

    return
        perdaPressaoECD;
}


double Resultados::getECDCalculada() const {

    return
        ecdCalculada;
}


double Resultados::getGradientePoroECD() const {

    return
        gradientePoroECD;
}


double Resultados::getGradienteFraturaECD() const {

    return
        gradienteFraturaECD;
}


const std::string&
Resultados::getClassificacaoECD() const {

    return
        classificacaoECD;
}


// ==========================================================
// EXPORTAÇÃO DAS JANELAS
// ==========================================================

bool Resultados::exportarDados(
    const std::string& caminhoArquivo
) const {

    std::ofstream arquivo(
        caminhoArquivo
    );


    if (
        !arquivo.is_open()
    ) {

        return
            false;
    }


    arquivo
        << "profundidade_m,"
        << "gradiente_poro_ppg,"
        << "gradiente_fratura_ppg,"
        << "largura_janela_ppg\n";


    arquivo
        << std::fixed
        << std::setprecision(6);


    for (
        const auto& janela :
        janelas
    ) {

        arquivo
            << janela.getProfundidade()
            << ","

            << janela.obterLimiteInferior()
            << ","

            << janela.obterLimiteSuperior()
            << ","

            << janela.getLarguraJanela()
            << '\n';
    }


    return
        true;
}


// ==========================================================
// EXPORTAÇÃO DO RESULTADO ECD
// ==========================================================

bool Resultados::exportarResultadoECD(
    const std::string& caminhoArquivo
) const {

    if (
        !possuiECD
    ) {

        return
            false;
    }


    std::ofstream arquivo(
        caminhoArquivo
    );


    if (
        !arquivo.is_open()
    ) {

        return
            false;
    }


    arquivo
        << "profundidade_m,"
        << "densidade_lama_ppg,"
        << "deltaPf_psi,"
        << "ecd_ppg,"
        << "gp_ppg,"
        << "gf_ppg,"
        << "classificacao\n";


    arquivo
        << std::fixed
        << std::setprecision(6)

        << profundidadeECD
        << ","

        << densidadeLamaECD
        << ","

        << perdaPressaoECD
        << ","

        << ecdCalculada
        << ","

        << gradientePoroECD
        << ","

        << gradienteFraturaECD
        << ",\""

        << classificacaoECD

        << "\"\n";


    return
        true;
}


// ==========================================================
// EXPORTAÇÃO COMPLETA DOS DADOS
// ==========================================================

bool Resultados::exportarDadosCompletos(
    const Poco& poco,
    const ParametrosSimulacao& parametros,
    const std::string& caminhoArquivo
) const {

    std::ofstream arquivo(
        caminhoArquivo
    );


    if (
        !arquivo.is_open()
    ) {

        return
            false;
    }


    arquivo
        << "indice,"
        << "topo_m,"
        << "base_m,"
        << "profundidade_media_m,"
        << "delta_t_us_ft,"
        << "delta_t_normal_us_ft,"
        << "porosidade,"
        << "porosidade_normal,"
        << "densidade_g_cm3,"
        << "densidade_lb_gal,"
        << "sigma_v_psi,"
        << "grad_sobrecarga_psi_ft,"
        << "grad_sobrecarga_ppg,"
        << "pressao_poro_psi,"
        << "gp_psi_ft,"
        << "gp_ppg,"
        << "shmin_psi,"
        << "gf_psi_ft,"
        << "gf_ppg\n";


    const auto& camadas =
        poco.getCamadas();


    for (
        const auto& camada :
        camadas
    ) {

        const double deltaTNormal =
            calcularDeltaTNormal(
                camada,
                parametros
            );


        const double phiNormal =
            calcularPorosidadeNormal(
                camada
            );


        const double densidadeLbGal =
            camada.getDensidadeBulk()
            *
            CONV_DENSITY;


        const double gradSobrecargaPsiFt =
            calcularGradienteSobrecargaPsiFt(
                camada
            );


        const double gradSobrecargaPpg =
            calcularGradienteSobrecargaPpg(
                camada
            );


        const double gpPpg =
            camada.getGradientePoro();


        const double gfPpg =
            camada.getGradienteFratura();


        const double gpPsiFt =
            valorValido(gpPpg)
            ?
            gpPpg * PSI_FT_PER_LB_GAL
            :
            std::numeric_limits<double>::
            quiet_NaN();


        const double gfPsiFt =
            valorValido(gfPpg)
            ?
            gfPpg * PSI_FT_PER_LB_GAL
            :
            std::numeric_limits<double>::
            quiet_NaN();


        arquivo
            << camada.getIndice()
            << ",";


        escreverNumero(
            arquivo,
            camada.getTopo()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getBase()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getProfundidadeMedia()
        );

        arquivo << ",";


        if (
            camada.possuiDeltaT()
        ) {

            escreverNumero(
                arquivo,
                camada.getDeltaT()
            );
        }
        else {

            arquivo
                << "NaN";
        }


        arquivo << ",";


        escreverNumero(
            arquivo,
            deltaTNormal
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getPorosidade()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            phiNormal
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getDensidadeBulk()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            densidadeLbGal
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getTensaoSobrecarga()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gradSobrecargaPsiFt
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gradSobrecargaPpg
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getPressaoPoro()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gpPsiFt
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gpPpg
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            camada.getTensaoHorizontalMinima()
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gfPsiFt
        );

        arquivo << ",";


        escreverNumero(
            arquivo,
            gfPpg
        );


        arquivo
            << '\n';
    }


    return
        true;
}
