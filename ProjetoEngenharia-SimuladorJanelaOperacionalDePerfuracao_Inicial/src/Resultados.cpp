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


// ==========================================================
// GERAÇÃO DOS GRÁFICOS
// ==========================================================

bool Resultados::gerarGraficos(
    const Poco& poco,
    const ParametrosSimulacao& parametros,
    const std::string& diretorioSaida
) const {

    namespace fs =
        std::filesystem;


    fs::create_directories(
        diretorioSaida
    );


    const fs::path diretorio(
        diretorioSaida
    );


    const fs::path caminhoCSV =
        diretorio
        /
        "dados_graficos.csv";


    const fs::path caminhoScript =
        diretorio
        /
        "gerar_graficos.gp";


    if (
        !exportarDadosCompletos(
            poco,
            parametros,
            caminhoCSV.string()
        )
    ) {

        return
            false;
    }


    std::ofstream script(
        caminhoScript
    );


    if (
        !script.is_open()
    ) {

        return
            false;
    }


    script
        << std::fixed
        << std::setprecision(6);


    const std::string csv =
        caminhoCSV.generic_string();


    const std::string pasta =
        diretorio.generic_string();


    // ======================================================
    // MONTA OS PONTOS VÁLIDOS DO ENVELOPE
    // ======================================================

    std::vector<PontoEnvelope>
    pontosEnvelope;


    double xMax =
        0.0;


    for (
        const auto& camada :
        poco.getCamadas()
    ) {

        const double gp =
            camada.getGradientePoro();


        const double gf =
            camada.getGradienteFratura();


        const double gov =
            calcularGradienteSobrecargaPpg(
                camada
            );


        if (
            valorValido(gp)
            &&
            valorValido(gf)
        ) {

            pontosEnvelope.push_back({

                camada.getProfundidadeMedia(),

                gp,

                gf,

                gov
            });
        }


        if (
            valorValido(gf)
        ) {

            xMax =
                std::max(
                    xMax,
                    gf
                );
        }


        if (
            valorValido(gov)
        ) {

            xMax =
                std::max(
                    xMax,
                    gov
                );
        }
    }


    xMax *=
        1.05;


    if (
        xMax <= 0.0
    ) {

        xMax =
            20.0;
    }


    // ======================================================
    // CONFIGURAÇÃO GERAL
    // ======================================================

    script
        << "set terminal pngcairo size 1400,900 enhanced "
        << "font 'Arial,14'\n"

        << "set datafile separator ','\n"

        << "set datafile missing 'NaN'\n"

        << "set grid\n"

        << "set border linewidth 1.5\n"

        << "set key opaque box\n\n";


    // ======================================================
    // GRÁFICO 1
    // PERFIL SÔNICO E TENDÊNCIA NORMAL
    // ======================================================

    script
        << "unset object\n";


    int idObjeto =
        1;


    const auto& camadas =
        poco.getCamadas();


    for (
        std::size_t i = 1;
        i < camadas.size();
        ++i
    ) {

        const auto& anterior =
            camadas[i - 1];


        const auto& atual =
            camadas[i];


        if (
            !anterior.possuiDeltaT()
            ||
            !atual.possuiDeltaT()
        ) {

            continue;
        }


        const double dtNormalAnterior =
            calcularDeltaTNormal(
                anterior,
                parametros
            );


        const double dtNormalAtual =
            calcularDeltaTNormal(
                atual,
                parametros
            );


        escreverPoligono(

            script,

            idObjeto++,

            anterior.getDeltaT(),
            anterior.getProfundidadeMedia(),

            dtNormalAnterior,
            anterior.getProfundidadeMedia(),

            dtNormalAtual,
            atual.getProfundidadeMedia(),

            atual.getDeltaT(),
            atual.getProfundidadeMedia(),

            "#7FBF7F",

            0.18
        );
    }


    script
        << "set output '"
        << pasta
        << "/01_perfil_sonico_tendencia.png'\n"

        << "set title 'Perfil Sonico e Tendencia Normal'\n"

        << "set xlabel 'Tempo de transito (us/ft)'\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set autoscale x\n"

        << "set yrange [*:*] reverse\n"

        << "set key bottom right\n"

        << "plot '"
        << csv
        << "' using 5:4 with lines lw 3 "
        << "lc rgb '#1F4E79' title 'Delta t observado', \\\n"

        << "     '"
        << csv
        << "' using 6:4 with lines lw 3 dt 2 "
        << "lc rgb '#F28E2B' title 'Delta t normal'\n"

        << "unset output\n"

        << "unset object\n\n";


    // ======================================================
    // GRÁFICO 2
    // POROSIDADE E DENSIDADE
    // ======================================================

    script
        << "set output '"
        << pasta
        << "/02_porosidade_densidade.png'\n"

        << "set multiplot layout 1,2 "
        << "title 'Porosidade e Densidade x Profundidade'\n"

        << "set autoscale x\n"

        << "set yrange [*:*] reverse\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set xlabel 'Porosidade (fracao)'\n"

        << "set title 'Porosidade x Profundidade'\n"

        << "set key top right\n"

        << "plot '"
        << csv
        << "' using 7:4 with lines lw 3 "
        << "lc rgb '#1F4E79' title 'Porosidade observada', \\\n"

        << "     '"
        << csv
        << "' using 8:4 with lines lw 3 dt 2 "
        << "lc rgb '#F28E2B' title 'Porosidade normal'\n"

        << "unset ylabel\n"

        << "set xlabel 'Densidade bulk (lb/gal)'\n"

        << "set title 'Densidade x Profundidade'\n"

        << "unset key\n"

        << "plot '"
        << csv
        << "' using 10:4 with lines lw 3 "
        << "lc rgb '#C00000' notitle\n"

        << "unset multiplot\n"

        << "unset output\n\n";


    // ======================================================
    // GRÁFICO 3
    // TENSÃO DE SOBRECARGA
    // ======================================================

    script
        << "set output '"
        << pasta
        << "/03_tensao_sobrecarga.png'\n"

        << "set title 'Tensao de Sobrecarga x Profundidade'\n"

        << "set xlabel 'Tensao de sobrecarga sigma_v (psi)'\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set autoscale x\n"

        << "set yrange [*:*] reverse\n"

        << "unset key\n"

        << "plot '"
        << csv
        << "' using 11:4 with lines lw 3 "
        << "lc rgb '#C00000'\n"

        << "unset output\n\n";


    // ======================================================
    // GRÁFICO 4
    // JANELA OPERACIONAL
    // ======================================================

    script
        << "unset object\n";


    idObjeto =
        1000;


    for (
        std::size_t i = 1;
        i < pontosEnvelope.size();
        ++i
    ) {

        const auto& p1 =
            pontosEnvelope[i - 1];


        const auto& p2 =
            pontosEnvelope[i];


        if (
            p1.gf > p1.gp
            &&
            p2.gf > p2.gp
        ) {

            escreverPoligono(

                script,

                idObjeto++,

                p1.gp,
                p1.profundidade,

                p1.gf,
                p1.profundidade,

                p2.gf,
                p2.profundidade,

                p2.gp,
                p2.profundidade,

                "#F7E26B",

                0.42
            );
        }
    }


    script
        << "set output '"
        << pasta
        << "/04_janela_operacional.png'\n"

        << "set title 'Janela Operacional de Perfuracao'\n"

        << "set xlabel 'Gradiente (lb/gal)'\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set autoscale x\n"

        << "set yrange [*:*] reverse\n"

        << "set key bottom left\n"

        << "plot '"
        << csv
        << "' using 16:4 with lines lw 3 "
        << "lc rgb '#000080' title 'Gradiente de Poro', \\\n"

        << "     '"
        << csv
        << "' using 19:4 with lines lw 3 "
        << "lc rgb '#008000' title 'Gradiente de Fratura', \\\n"

        << "     '"
        << csv
        << "' using 13:4 with lines lw 3 "
        << "lc rgb '#C00000' title 'Gradiente de Sobrecarga'\n"

        << "unset output\n"

        << "unset object\n\n";


    // ======================================================
    // GRÁFICO 5
    // GRADIENTES EM PSI/FT
    // ======================================================

    const double gradienteHidroDeslocado =
        parametros
            .getGradienteHidrostaticoNormal()
        +
        0.312;


    script
        << "set output '"
        << pasta
        << "/05_gradientes_psi_ft.png'\n"

        << "set title 'Comparacao de Gradientes de Pressao'\n"

        << "set xlabel 'Gradiente (psi/ft)'\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set autoscale x\n"

        << "set yrange [*:*] reverse\n"

        << "set key bottom left\n"

        << "plot '"
        << csv
        << "' using 15:4 with lines lw 3 "
        << "lc rgb '#000080' title 'Gradiente de Poro', \\\n"

        << "     '"
        << csv
        << "' using 18:4 with lines lw 3 "
        << "lc rgb '#008000' title 'Gradiente de Fratura', \\\n"

        << "     '"
        << csv
        << "' using 12:4 with lines lw 3 "
        << "lc rgb '#C00000' title 'Gradiente de Sobrecarga', \\\n"

        << "     '"
        << csv
        << "' using ("
        << gradienteHidroDeslocado
        << "):4 with lines lw 2 dt 2 "
        << "lc rgb '#00A6D6' "
        << "title 'Gradiente Hidrostatico deslocado'\n"

        << "unset output\n\n";


    // ======================================================
    // GRÁFICO 6
    // MUD WEIGHT OPERATIONAL ENVELOPE
    // ======================================================

    script
        << "unset object\n";


    idObjeto =
        2000;


    for (
        std::size_t i = 1;
        i < pontosEnvelope.size();
        ++i
    ) {

        const auto& p1 =
            pontosEnvelope[i - 1];


        const auto& p2 =
            pontosEnvelope[i];


        if (
            p1.gf <= p1.gp
            ||
            p2.gf <= p2.gp
        ) {

            continue;
        }


        // ==================================================
        // ZONA DE KICK
        // ==================================================

        escreverPoligono(

            script,

            idObjeto++,

            0.0,
            p1.profundidade,

            p1.gp,
            p1.profundidade,

            p2.gp,
            p2.profundidade,

            0.0,
            p2.profundidade,

            "#A9D6E5",

            0.38
        );


        // ==================================================
        // JANELA SEGURA
        // ==================================================

        escreverPoligono(

            script,

            idObjeto++,

            p1.gp,
            p1.profundidade,

            p1.gf,
            p1.profundidade,

            p2.gf,
            p2.profundidade,

            p2.gp,
            p2.profundidade,

            "#F7E26B",

            0.42
        );


        // ==================================================
        // ZONA DE LOSS
        // ==================================================

        escreverPoligono(

            script,

            idObjeto++,

            p1.gf,
            p1.profundidade,

            xMax,
            p1.profundidade,

            xMax,
            p2.profundidade,

            p2.gf,
            p2.profundidade,

            "#F28E8E",

            0.38
        );
    }


    script
        << "set output '"
        << pasta
        << "/06_mud_weight_operational_envelope.png'\n"

        << "set title 'Limites Operacionais de Densidade de Lama'\n"

        << "set xlabel 'Gradiente / Peso de Lama (lb/gal)'\n"

        << "set ylabel 'Profundidade (m)'\n"

        << "set xrange [0:"
        << xMax
        << "]\n"

        << "set yrange [*:*] reverse\n"

        << "set key top left\n"

        << "plot '"
        << csv
        << "' using 16:4 with lines lw 3 "
        << "lc rgb '#000080' title 'Gradiente de Poro', \\\n"

        << "     '"
        << csv
        << "' using 19:4 with lines lw 3 "
        << "lc rgb '#008000' title 'Gradiente de Fratura', \\\n"

        << "     '"
        << csv
        << "' using 13:4 with lines lw 3 "
        << "lc rgb '#C00000' title 'Gradiente de Sobrecarga'\n"

        << "unset output\n"

        << "unset object\n\n";


    // ======================================================
    // GRÁFICO 7
    // ECD NO MUD WEIGHT OPERATIONAL ENVELOPE
    // ======================================================

    if (
        possuiECD
    ) {

        idObjeto =
            3000;


        for (
            std::size_t i = 1;
            i < pontosEnvelope.size();
            ++i
        ) {

            const auto& p1 =
                pontosEnvelope[i - 1];


            const auto& p2 =
                pontosEnvelope[i];


            if (
                p1.gf <= p1.gp
                ||
                p2.gf <= p2.gp
            ) {

                continue;
            }


            // KICK

            escreverPoligono(

                script,

                idObjeto++,

                0.0,
                p1.profundidade,

                p1.gp,
                p1.profundidade,

                p2.gp,
                p2.profundidade,

                0.0,
                p2.profundidade,

                "#A9D6E5",

                0.35
            );


            // JANELA OPERACIONAL

            escreverPoligono(

                script,

                idObjeto++,

                p1.gp,
                p1.profundidade,

                p1.gf,
                p1.profundidade,

                p2.gf,
                p2.profundidade,

                p2.gp,
                p2.profundidade,

                "#F7E26B",

                0.38
            );


            // LOSS

            escreverPoligono(

                script,

                idObjeto++,

                p1.gf,
                p1.profundidade,

                xMax,
                p1.profundidade,

                xMax,
                p2.profundidade,

                p2.gf,
                p2.profundidade,

                "#F28E8E",

                0.35
            );
        }


        script
            << "set output '"
            << pasta
            << "/07_ecd_operational_envelope.png'\n"

            << "set title 'ECD na Mud Weight Operational Envelope'\n"

            << "set xlabel 'Gradiente / Peso de Lama (lb/gal)'\n"

            << "set ylabel 'Profundidade (m)'\n"

            << "set xrange [0:"
            << xMax
            << "]\n"

            << "set yrange [*:*] reverse\n"

            << "set key top left\n"

            << "plot '"
            << csv
            << "' using 16:4 with lines lw 3 "
            << "lc rgb '#000080' title 'Gradiente de Poro', \\\n"

            << "     '"
            << csv
            << "' using 19:4 with lines lw 3 "
            << "lc rgb '#008000' title 'Gradiente de Fratura', \\\n"

            << "     '"
            << csv
            << "' using 13:4 with lines lw 3 "
            << "lc rgb '#C00000' title 'Gradiente de Sobrecarga', \\\n"

            << "     '+' using ("
            << ecdCalculada
            << "):("
            << profundidadeECD
            << ") with points pt 7 ps 2.4 "
            << "lc rgb 'black' title 'ECD calculada'\n"

            << "unset output\n"

            << "unset object\n\n";
    }


    script.close();


    // ======================================================
    // EXECUTA O GNUPLOT
    // ======================================================

    const std::string comando =
        "gnuplot \""
        +
        caminhoScript.string()
        +
        "\"";


    const int resultado =
        std::system(
            comando.c_str()
        );


    return
        resultado == 0;
}