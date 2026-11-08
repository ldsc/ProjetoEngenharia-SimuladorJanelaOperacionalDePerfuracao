#include "MainWindow.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <cmath>
#include <exception>
#include <limits>


// ==========================================================
// CONSTRUTOR
// ==========================================================

MainWindow::MainWindow(
    QWidget* parent
)
    : QMainWindow(parent),

      abas(nullptr),

      labelArquivoPoco(nullptr),
      labelNumeroCamadas(nullptr),
      labelProfundidadeMaxima(nullptr),
      labelStatusDados(nullptr),
      botaoSelecionarPoco(nullptr),

      labelArquivoParametros(nullptr),
      labelStatusParametros(nullptr),
      botaoSelecionarParametros(nullptr),
      botaoAplicarParametros(nullptr),

      campoDensidadeMatriz(nullptr),
      campoDensidadeFluido(nullptr),
      campoDensidadeAguaMar(nullptr),
      campoDensidadeSedimento(nullptr),
      campoDeltaTMatriz(nullptr),
      campoDeltaTFluido(nullptr),
      campoPorosidadeSedimento(nullptr),
      campoPorosidadeMinima(nullptr),
      campoPorosidadeMaxima(nullptr),

      campoGradienteHidrostatico(nullptr),
      campoExpoenteEaton(nullptr),
      campoCoeficientePoisson(nullptr),
      campoDeltaTReferencia(nullptr),
      campoConstanteCompactacao(nullptr),

      campoDensidadeLamaECD(nullptr),
      campoPerdaPressaoECD(nullptr),
      campoProfundidadeECD(nullptr),
      botaoExecutarSimulacao(nullptr),
      labelStatusSimulacao(nullptr),
      labelProfundidadeSolicitada(nullptr),
      labelProfundidadeAvaliada(nullptr),
      labelECDCalculada(nullptr),
      labelGradientePoroECD(nullptr),
      labelGradienteFraturaECD(nullptr),
      labelClassificacaoECD(nullptr),

      labelResumoResultados(nullptr),
      tabelaResultados(nullptr),
      botaoExportarResultados(nullptr),

      labelStatusGraficos(nullptr),
      botaoGerarGraficos(nullptr),
      comboGraficos(nullptr),
      areaVisualizacaoGrafico(nullptr),
      labelImagemGrafico(nullptr)
{

    criarInterface();

    atualizarCamposParametros();
}


// ==========================================================
// DESTRUTOR
// ==========================================================

MainWindow::~MainWindow()
{
}


// ==========================================================
// INTERFACE PRINCIPAL
// ==========================================================

void MainWindow::criarInterface()
{

    setWindowTitle(
        "Simulador de Janela Operacional de Perfuracao"
    );


    resize(
        1200,
        750
    );


    QWidget* widgetCentral =
        new QWidget(this);


    QVBoxLayout* layoutPrincipal =
        new QVBoxLayout(widgetCentral);


    QLabel* titulo =
        new QLabel(
            "Simulador de Janela Operacional de Perfuracao",
            widgetCentral
        );


    QFont fonteTitulo =
        titulo->font();


    fonteTitulo.setPointSize(
        18
    );


    fonteTitulo.setBold(
        true
    );


    titulo->setFont(
        fonteTitulo
    );


    titulo->setAlignment(
        Qt::AlignCenter
    );


    layoutPrincipal->addWidget(
        titulo
    );


    abas =
        new QTabWidget(
            widgetCentral
        );


    layoutPrincipal->addWidget(
        abas
    );


    setCentralWidget(
        widgetCentral
    );


    criarAbaDadosPoco();

    criarAbaParametros();

    criarAbaECD();

    criarAbaResultados();

    criarAbaGraficos();
}


// ==========================================================
// ABA 1 - DADOS DO POÇO
// ==========================================================

void MainWindow::criarAbaDadosPoco()
{

    QWidget* pagina =
        new QWidget();


    QVBoxLayout* layout =
        new QVBoxLayout(
            pagina
        );


    QLabel* titulo =
        new QLabel(
            "Dados do Poco"
        );


    QFont fonte =
        titulo->font();


    fonte.setPointSize(
        14
    );


    fonte.setBold(
        true
    );


    titulo->setFont(
        fonte
    );


    layout->addWidget(
        titulo
    );


    QLabel* descricao =
        new QLabel(
            "Selecione o arquivo CSV contendo profundidade, "
            "perfil sonico e tipo das camadas."
        );


    descricao->setWordWrap(
        true
    );


    layout->addWidget(
        descricao
    );


    QGroupBox* grupoArquivo =
        new QGroupBox(
            "Arquivo de dados do poco"
        );


    QVBoxLayout* layoutArquivo =
        new QVBoxLayout(
            grupoArquivo
        );


    labelArquivoPoco =
        new QLabel(
            "Nenhum arquivo selecionado."
        );


    labelArquivoPoco->setWordWrap(
        true
    );


    layoutArquivo->addWidget(
        labelArquivoPoco
    );


    botaoSelecionarPoco =
        new QPushButton(
            "Selecionar arquivo CSV"
        );


    layoutArquivo->addWidget(
        botaoSelecionarPoco
    );


    layout->addWidget(
        grupoArquivo
    );


    QGroupBox* grupoInformacoes =
        new QGroupBox(
            "Informacoes carregadas"
        );


    QVBoxLayout* layoutInformacoes =
        new QVBoxLayout(
            grupoInformacoes
        );


    labelNumeroCamadas =
        new QLabel(
            "Numero de camadas: --"
        );


    labelProfundidadeMaxima =
        new QLabel(
            "Profundidade maxima: --"
        );


    labelStatusDados =
        new QLabel(
            "Status: aguardando arquivo."
        );


    layoutInformacoes->addWidget(
        labelNumeroCamadas
    );


    layoutInformacoes->addWidget(
        labelProfundidadeMaxima
    );


    layoutInformacoes->addWidget(
        labelStatusDados
    );


    layout->addWidget(
        grupoInformacoes
    );


    layout->addStretch();


    connect(

        botaoSelecionarPoco,

        &QPushButton::clicked,

        this,

        &MainWindow::selecionarArquivoPoco
    );


    abas->addTab(
        pagina,
        "Dados do Poco"
    );
}


// ==========================================================
// SELECIONAR CSV DO POÇO
// ==========================================================

void MainWindow::selecionarArquivoPoco()
{

    const QString caminhoArquivo =
        QFileDialog::getOpenFileName(

            this,

            "Selecionar arquivo de dados do poco",

            QString(),

            "Arquivos CSV (*.csv);;Todos os arquivos (*.*)"
        );


    if (
        caminhoArquivo.isEmpty()
    ) {

        return;
    }


    try {

        ParametrosSimulacao parametrosAtuais =
            simulador.getParametros();


        SimuladorJanelaOperacional novoSimulador;


        novoSimulador.getParametros() =
            parametrosAtuais;


        const bool carregado =
            novoSimulador.carregarDadosCSV(

                caminhoArquivo.toStdString()
            );


        if (
            !carregado
        ) {

            QMessageBox::critical(

                this,

                "Erro ao carregar arquivo",

                "Nao foi possivel carregar o arquivo selecionado."
            );


            return;
        }


        simulador =
            novoSimulador;


        labelArquivoPoco->setText(

            "Arquivo selecionado:\n"
            +
            caminhoArquivo
        );


        labelNumeroCamadas->setText(

            "Numero de camadas: "
            +
            QString::number(

                simulador
                    .getPoco()
                    .obterNumeroCamadas()
            )
        );


        labelProfundidadeMaxima->setText(

            "Profundidade maxima: "
            +
            QString::number(

                simulador
                    .getPoco()
                    .getProfundidadeMaxima(),

                'f',

                2
            )
            +
            " m"
        );


        labelStatusDados->setText(
            "Status: dados carregados com sucesso."
        );


        labelStatusSimulacao->setText(
            "Status: aguardando execucao."
        );


        if (
            tabelaResultados != nullptr
        ) {

            tabelaResultados->setRowCount(
                0
            );
        }


        if (
            labelResumoResultados != nullptr
        ) {

            labelResumoResultados->setText(
                "Execute a simulacao para visualizar os resultados."
            );
        }


        limparGraficosInterface();


        QMessageBox::information(

            this,

            "Dados carregados",

            "Arquivo do poco carregado com sucesso."
        );
    }


    catch (
        const std::exception& erro
    ) {

        QMessageBox::critical(

            this,

            "Erro nos dados do poco",

            QString(
                "O arquivo nao pode ser carregado.\n\nErro: "
            )
            +
            QString::fromStdString(
                erro.what()
            )
        );


        labelStatusDados->setText(
            "Status: erro ao carregar arquivo."
        );
    }
}


// ==========================================================
// ABA 2 - PARÂMETROS
// ==========================================================

void MainWindow::criarAbaParametros()
{

    QWidget* pagina =
        new QWidget();


    QVBoxLayout* layoutPagina =
        new QVBoxLayout(
            pagina
        );


    QLabel* titulo =
        new QLabel(
            "Parametros da Simulacao"
        );


    QFont fonte =
        titulo->font();


    fonte.setPointSize(
        14
    );


    fonte.setBold(
        true
    );


    titulo->setFont(
        fonte
    );


    layoutPagina->addWidget(
        titulo
    );


    QLabel* descricao =
        new QLabel(
            "Os valores abaixo podem ser carregados por arquivo CSV "
            "ou editados diretamente pelo usuario."
        );


    descricao->setWordWrap(
        true
    );


    layoutPagina->addWidget(
        descricao
    );


    QGroupBox* grupoArquivo =
        new QGroupBox(
            "Arquivo de parametros"
        );


    QVBoxLayout* layoutArquivo =
        new QVBoxLayout(
            grupoArquivo
        );


    labelArquivoParametros =
        new QLabel(
            "Nenhum arquivo de parametros selecionado."
        );


    labelArquivoParametros->setWordWrap(
        true
    );


    botaoSelecionarParametros =
        new QPushButton(
            "Carregar parametros CSV"
        );


    layoutArquivo->addWidget(
        labelArquivoParametros
    );


    layoutArquivo->addWidget(
        botaoSelecionarParametros
    );


    layoutPagina->addWidget(
        grupoArquivo
    );


    // ======================================================
    // ÁREA ROLÁVEL
    // ======================================================

    QScrollArea* areaRolavel =
        new QScrollArea();


    areaRolavel->setWidgetResizable(
        true
    );


    QWidget* conteudo =
        new QWidget();


    QVBoxLayout* layoutConteudo =
        new QVBoxLayout(
            conteudo
        );


    // ======================================================
    // PETROFÍSICA
    // ======================================================

    QGroupBox* grupoPetrofisica =
        new QGroupBox(
            "Parametros Petrofisicos"
        );


    QFormLayout* formularioPetrofisica =
        new QFormLayout(
            grupoPetrofisica
        );


    campoDensidadeMatriz =
        new QDoubleSpinBox();


    campoDensidadeMatriz->setRange(
        0.1,
        5.0
    );


    campoDensidadeMatriz->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Densidade da matriz (g/cm3):",
        campoDensidadeMatriz
    );


    campoDensidadeFluido =
        new QDoubleSpinBox();


    campoDensidadeFluido->setRange(
        0.1,
        5.0
    );


    campoDensidadeFluido->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Densidade do fluido (g/cm3):",
        campoDensidadeFluido
    );


    campoDensidadeAguaMar =
        new QDoubleSpinBox();


    campoDensidadeAguaMar->setRange(
        0.1,
        5.0
    );


    campoDensidadeAguaMar->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Densidade da agua do mar (g/cm3):",
        campoDensidadeAguaMar
    );


    campoDensidadeSedimento =
        new QDoubleSpinBox();


    campoDensidadeSedimento->setRange(
        0.1,
        5.0
    );


    campoDensidadeSedimento->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Densidade do sedimento (g/cm3):",
        campoDensidadeSedimento
    );


    campoDeltaTMatriz =
        new QDoubleSpinBox();


    campoDeltaTMatriz->setRange(
        1.0,
        500.0
    );


    campoDeltaTMatriz->setDecimals(
        3
    );


    formularioPetrofisica->addRow(
        "Delta t da matriz (us/ft):",
        campoDeltaTMatriz
    );


    campoDeltaTFluido =
        new QDoubleSpinBox();


    campoDeltaTFluido->setRange(
        1.0,
        500.0
    );


    campoDeltaTFluido->setDecimals(
        3
    );


    formularioPetrofisica->addRow(
        "Delta t do fluido (us/ft):",
        campoDeltaTFluido
    );


    campoPorosidadeSedimento =
        new QDoubleSpinBox();


    campoPorosidadeSedimento->setRange(
        0.0,
        1.0
    );


    campoPorosidadeSedimento->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Porosidade do sedimento:",
        campoPorosidadeSedimento
    );


    campoPorosidadeMinima =
        new QDoubleSpinBox();


    campoPorosidadeMinima->setRange(
        0.0,
        1.0
    );


    campoPorosidadeMinima->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Porosidade minima:",
        campoPorosidadeMinima
    );


    campoPorosidadeMaxima =
        new QDoubleSpinBox();


    campoPorosidadeMaxima->setRange(
        0.0,
        1.0
    );


    campoPorosidadeMaxima->setDecimals(
        4
    );


    formularioPetrofisica->addRow(
        "Porosidade maxima:",
        campoPorosidadeMaxima
    );


    layoutConteudo->addWidget(
        grupoPetrofisica
    );


    // ======================================================
    // GEOPRESSÕES
    // ======================================================

    QGroupBox* grupoGeopressoes =
        new QGroupBox(
            "Geopressoes e Geomecanica"
        );


    QFormLayout* formularioGeopressoes =
        new QFormLayout(
            grupoGeopressoes
        );


    campoGradienteHidrostatico =
        new QDoubleSpinBox();


    campoGradienteHidrostatico->setRange(
        0.01,
        2.0
    );


    campoGradienteHidrostatico->setDecimals(
        6
    );


    formularioGeopressoes->addRow(
        "Gradiente hidrostatico normal (psi/ft):",
        campoGradienteHidrostatico
    );


    campoExpoenteEaton =
        new QDoubleSpinBox();


    campoExpoenteEaton->setRange(
        0.1,
        10.0
    );


    campoExpoenteEaton->setDecimals(
        4
    );


    formularioGeopressoes->addRow(
        "Expoente de Eaton:",
        campoExpoenteEaton
    );


    campoCoeficientePoisson =
        new QDoubleSpinBox();


    campoCoeficientePoisson->setRange(
        0.0001,
        0.4999
    );


    campoCoeficientePoisson->setDecimals(
        4
    );


    formularioGeopressoes->addRow(
        "Coeficiente de Poisson:",
        campoCoeficientePoisson
    );


    campoDeltaTReferencia =
        new QDoubleSpinBox();


    campoDeltaTReferencia->setRange(
        1.0,
        500.0
    );


    campoDeltaTReferencia->setDecimals(
        3
    );


    formularioGeopressoes->addRow(
        "Delta t de referencia (us/ft):",
        campoDeltaTReferencia
    );


    campoConstanteCompactacao =
        new QDoubleSpinBox();


    campoConstanteCompactacao->setRange(
        0.0,
        1.0
    );


    campoConstanteCompactacao->setDecimals(
        7
    );


    formularioGeopressoes->addRow(
        "Constante de compactacao:",
        campoConstanteCompactacao
    );


    layoutConteudo->addWidget(
        grupoGeopressoes
    );


    layoutConteudo->addStretch();


    areaRolavel->setWidget(
        conteudo
    );


    layoutPagina->addWidget(
        areaRolavel
    );


    botaoAplicarParametros =
        new QPushButton(
            "Aplicar parametros"
        );


    layoutPagina->addWidget(
        botaoAplicarParametros
    );


    labelStatusParametros =
        new QLabel(
            "Status: utilizando valores padrao."
        );


    layoutPagina->addWidget(
        labelStatusParametros
    );


    connect(

        botaoSelecionarParametros,

        &QPushButton::clicked,

        this,

        &MainWindow::selecionarArquivoParametros
    );


    connect(

        botaoAplicarParametros,

        &QPushButton::clicked,

        this,

        &MainWindow::aplicarParametrosInterface
    );


    abas->addTab(
        pagina,
        "Parametros"
    );
}


// ==========================================================
// ATUALIZA CAMPOS DE PARÂMETROS
// ==========================================================

void MainWindow::atualizarCamposParametros()
{

    const ParametrosSimulacao& parametros =
        simulador.getParametros();


    if (
        campoDensidadeMatriz != nullptr
    ) {

        campoDensidadeMatriz->setValue(
            parametros.getDensidadeMatriz()
        );


        campoDensidadeFluido->setValue(
            parametros.getDensidadeFluido()
        );


        campoDensidadeAguaMar->setValue(
            parametros.getDensidadeAguaMar()
        );


        campoDensidadeSedimento->setValue(
            parametros.getDensidadeSedimento()
        );


        campoDeltaTMatriz->setValue(
            parametros.getDeltaTMatriz()
        );


        campoDeltaTFluido->setValue(
            parametros.getDeltaTFluido()
        );


        campoPorosidadeSedimento->setValue(
            parametros.getPorosidadeSedimento()
        );


        campoPorosidadeMinima->setValue(
            parametros.getPorosidadeMinima()
        );


        campoPorosidadeMaxima->setValue(
            parametros.getPorosidadeMaxima()
        );


        campoGradienteHidrostatico->setValue(
            parametros.getGradienteHidrostaticoNormal()
        );


        campoExpoenteEaton->setValue(
            parametros.getExpoenteEaton()
        );


        campoCoeficientePoisson->setValue(
            parametros.getCoeficientePoisson()
        );


        campoDeltaTReferencia->setValue(
            parametros.getDeltaTReferencia()
        );


        campoConstanteCompactacao->setValue(
            parametros.getConstanteCompactacao()
        );
    }


    if (
        campoDensidadeLamaECD != nullptr
    ) {

        campoDensidadeLamaECD->setValue(
            parametros.getDensidadeLama()
        );


        campoPerdaPressaoECD->setValue(
            parametros.getPerdaPressaoECD()
        );


        campoProfundidadeECD->setValue(
            parametros.getProfundidadeECD()
        );
    }
}


// ==========================================================
// CARREGAR CSV DE PARÂMETROS
// ==========================================================

void MainWindow::selecionarArquivoParametros()
{

    const QString caminhoArquivo =
        QFileDialog::getOpenFileName(

            this,

            "Selecionar arquivo de parametros",

            QString(),

            "Arquivos CSV (*.csv);;Todos os arquivos (*.*)"
        );


    if (
        caminhoArquivo.isEmpty()
    ) {

        return;
    }


    try {

        SimuladorJanelaOperacional simuladorTemporario =
            simulador;


        const bool carregado =
            simuladorTemporario.carregarParametrosCSV(

                caminhoArquivo.toStdString()
            );


        if (
            !carregado
        ) {

            QMessageBox::critical(

                this,

                "Erro ao carregar parametros",

                "Nao foi possivel abrir o arquivo selecionado."
            );


            return;
        }


        simulador =
            simuladorTemporario;


        // Resultados antigos deixam de ser válidos.
        simulador
            .getResultados()
            .definirSimulacaoValida(
                false
            );


        atualizarCamposParametros();


        if (
            tabelaResultados != nullptr
        ) {

            tabelaResultados->setRowCount(
                0
            );
        }


        if (
            labelResumoResultados != nullptr
        ) {

            labelResumoResultados->setText(
                "Parametros alterados. Execute novamente a simulacao."
            );
        }


        limparGraficosInterface();


        labelArquivoParametros->setText(

            "Arquivo selecionado:\n"
            +
            caminhoArquivo
        );


        labelStatusParametros->setText(
            "Status: parametros carregados com sucesso."
        );


        QMessageBox::information(

            this,

            "Parametros carregados",

            "Os parametros foram carregados e aplicados com sucesso."
        );
    }


    catch (
        const std::exception& erro
    ) {

        QMessageBox::critical(

            this,

            "Erro nos parametros",

            QString(
                "Nao foi possivel carregar os parametros.\n\nErro: "
            )
            +
            QString::fromStdString(
                erro.what()
            )
        );


        labelStatusParametros->setText(
            "Status: erro ao carregar parametros."
        );
    }
}


// ==========================================================
// APLICAR PARÂMETROS DA INTERFACE
// ==========================================================

void MainWindow::aplicarParametrosInterface()
{

    ParametrosSimulacao novosParametros =
        simulador.getParametros();


    novosParametros.definirDensidadeMatriz(
        campoDensidadeMatriz->value()
    );


    novosParametros.definirDensidadeFluido(
        campoDensidadeFluido->value()
    );


    novosParametros.definirDensidadeAguaMar(
        campoDensidadeAguaMar->value()
    );


    novosParametros.definirDensidadeSedimento(
        campoDensidadeSedimento->value()
    );


    novosParametros.definirDeltaTMatriz(
        campoDeltaTMatriz->value()
    );


    novosParametros.definirDeltaTFluido(
        campoDeltaTFluido->value()
    );


    novosParametros.definirPorosidadeSedimento(
        campoPorosidadeSedimento->value()
    );


    novosParametros.definirLimitesPorosidade(

        campoPorosidadeMinima->value(),

        campoPorosidadeMaxima->value()
    );


    novosParametros.definirGradienteHidrostatico(
        campoGradienteHidrostatico->value()
    );


    novosParametros.definirExpoenteEaton(
        campoExpoenteEaton->value()
    );


    novosParametros.definirCoeficientePoisson(
        campoCoeficientePoisson->value()
    );


    novosParametros.definirDeltaTReferencia(
        campoDeltaTReferencia->value()
    );


    novosParametros.definirConstanteCompactacao(
        campoConstanteCompactacao->value()
    );


    if (
        !novosParametros.validarParametros()
    ) {

        QMessageBox::warning(

            this,

            "Parametros invalidos",

            "Um ou mais valores informados sao fisicamente invalidos."
        );


        labelStatusParametros->setText(
            "Status: parametros invalidos."
        );


        return;
    }


    simulador.getParametros() =
        novosParametros;


    simulador
        .getResultados()
        .definirSimulacaoValida(
            false
        );


    if (
        tabelaResultados != nullptr
    ) {

        tabelaResultados->setRowCount(
            0
        );
    }


    if (
        labelResumoResultados != nullptr
    ) {

        labelResumoResultados->setText(
            "Parametros alterados. Execute novamente a simulacao."
        );
    }


    limparGraficosInterface();


    labelStatusParametros->setText(
        "Status: parametros aplicados com sucesso."
    );


    QMessageBox::information(

        this,

        "Parametros aplicados",

        "Os valores informados foram aplicados ao simulador."
    );
}


// ==========================================================
// ABA 3 - ECD
// ==========================================================

void MainWindow::criarAbaECD()
{

    QWidget* pagina =
        new QWidget();


    QVBoxLayout* layout =
        new QVBoxLayout(
            pagina
        );


    QLabel* titulo =
        new QLabel(
            "Analise de ECD"
        );


    QFont fonte =
        titulo->font();


    fonte.setPointSize(
        14
    );


    fonte.setBold(
        true
    );


    titulo->setFont(
        fonte
    );


    layout->addWidget(
        titulo
    );


    QLabel* descricao =
        new QLabel(
            "Informe os parametros operacionais e execute "
            "a simulacao completa."
        );


    descricao->setWordWrap(
        true
    );


    layout->addWidget(
        descricao
    );


    QGroupBox* grupoEntrada =
        new QGroupBox(
            "Parametros operacionais"
        );


    QFormLayout* formulario =
        new QFormLayout(
            grupoEntrada
        );


    campoDensidadeLamaECD =
        new QDoubleSpinBox();


    campoDensidadeLamaECD->setRange(
        0.1,
        30.0
    );


    campoDensidadeLamaECD->setDecimals(
        4
    );


    formulario->addRow(
        "Densidade da lama (lb/gal):",
        campoDensidadeLamaECD
    );


    campoPerdaPressaoECD =
        new QDoubleSpinBox();


    campoPerdaPressaoECD->setRange(
        0.0,
        100000.0
    );


    campoPerdaPressaoECD->setDecimals(
        2
    );


    formulario->addRow(
        "Perda de pressao (psi):",
        campoPerdaPressaoECD
    );


    campoProfundidadeECD =
        new QDoubleSpinBox();


    campoProfundidadeECD->setRange(
        0.1,
        20000.0
    );


    campoProfundidadeECD->setDecimals(
        3
    );


    formulario->addRow(
        "Profundidade de avaliacao (m):",
        campoProfundidadeECD
    );


    layout->addWidget(
        grupoEntrada
    );


    botaoExecutarSimulacao =
        new QPushButton(
            "EXECUTAR SIMULACAO"
        );


    QFont fonteBotao =
        botaoExecutarSimulacao->font();


    fonteBotao.setBold(
        true
    );


    fonteBotao.setPointSize(
        12
    );


    botaoExecutarSimulacao->setFont(
        fonteBotao
    );


    botaoExecutarSimulacao->setMinimumHeight(
        45
    );


    layout->addWidget(
        botaoExecutarSimulacao
    );


    labelStatusSimulacao =
        new QLabel(
            "Status: aguardando execucao."
        );


    layout->addWidget(
        labelStatusSimulacao
    );


    QGroupBox* grupoResultado =
        new QGroupBox(
            "Resultado da analise"
        );


    QVBoxLayout* layoutResultado =
        new QVBoxLayout(
            grupoResultado
        );


    labelProfundidadeSolicitada =
        new QLabel(
            "Profundidade solicitada: --"
        );


    labelProfundidadeAvaliada =
        new QLabel(
            "Camada avaliada: --"
        );


    labelECDCalculada =
        new QLabel(
            "ECD calculada: --"
        );


    labelGradientePoroECD =
        new QLabel(
            "Gradiente de poro (Gp): --"
        );


    labelGradienteFraturaECD =
        new QLabel(
            "Gradiente de fratura (Gf): --"
        );


    labelClassificacaoECD =
        new QLabel(
            "Classificacao: --"
        );


    labelClassificacaoECD->setWordWrap(
        true
    );


    layoutResultado->addWidget(
        labelProfundidadeSolicitada
    );


    layoutResultado->addWidget(
        labelProfundidadeAvaliada
    );


    layoutResultado->addWidget(
        labelECDCalculada
    );


    layoutResultado->addWidget(
        labelGradientePoroECD
    );


    layoutResultado->addWidget(
        labelGradienteFraturaECD
    );


    layoutResultado->addWidget(
        labelClassificacaoECD
    );


    layout->addWidget(
        grupoResultado
    );


    layout->addStretch();


    connect(

        botaoExecutarSimulacao,

        &QPushButton::clicked,

        this,

        &MainWindow::executarSimulacaoInterface
    );


    abas->addTab(
        pagina,
        "ECD"
    );
}


// ==========================================================
// EXECUTAR SIMULAÇÃO
// ==========================================================

void MainWindow::executarSimulacaoInterface()
{

    try {

        if (
            simulador
                .getPoco()
                .obterNumeroCamadas()
            == 0
        ) {

            QMessageBox::warning(

                this,

                "Dados do poco ausentes",

                "Carregue primeiro um arquivo CSV na aba Dados do Poco."
            );


            abas->setCurrentIndex(
                0
            );


            return;
        }


        ParametrosSimulacao parametros =
            simulador.getParametros();


        parametros.definirDensidadeLama(
            campoDensidadeLamaECD->value()
        );


        parametros.definirPerdaPressaoECD(
            campoPerdaPressaoECD->value()
        );


        parametros.definirProfundidadeECD(
            campoProfundidadeECD->value()
        );


        if (
            !parametros.validarParametros()
        ) {

            QMessageBox::warning(

                this,

                "Parametros invalidos",

                "Os parametros informados para a simulacao sao invalidos."
            );


            return;
        }


        simulador.getParametros() =
            parametros;


        labelStatusSimulacao->setText(
            "Status: executando simulacao..."
        );


        QApplication::processEvents();


        simulador.executarSimulacao();


        simulador.avaliarECD(

            parametros.getDensidadeLama(),

            parametros.getPerdaPressaoECD(),

            parametros.getProfundidadeECD()
        );


        Resultados& resultados =
            simulador.getResultados();


        labelProfundidadeSolicitada->setText(

            "Profundidade solicitada: "
            +
            QString::number(
                parametros.getProfundidadeECD(),
                'f',
                3
            )
            +
            " m"
        );


        labelProfundidadeAvaliada->setText(

            "Camada avaliada: "
            +
            QString::number(
                resultados.getProfundidadeECD(),
                'f',
                6
            )
            +
            " m"
        );


        labelECDCalculada->setText(

            "ECD calculada: "
            +
            QString::number(
                resultados.getECDCalculada(),
                'f',
                6
            )
            +
            " lb/gal"
        );


        labelGradientePoroECD->setText(

            "Gradiente de poro (Gp): "
            +
            QString::number(
                resultados.getGradientePoroECD(),
                'f',
                6
            )
            +
            " lb/gal"
        );


        labelGradienteFraturaECD->setText(

            "Gradiente de fratura (Gf): "
            +
            QString::number(
                resultados.getGradienteFraturaECD(),
                'f',
                6
            )
            +
            " lb/gal"
        );


        labelClassificacaoECD->setText(

            "Classificacao: "
            +
            QString::fromStdString(
                resultados.getClassificacaoECD()
            )
        );


        atualizarTabelaResultados();


        limparGraficosInterface();


        labelStatusGraficos->setText(
            "Status: simulacao concluida. "
            "Clique em Gerar / Atualizar Graficos."
        );


        labelStatusSimulacao->setText(
            "Status: simulacao concluida com sucesso."
        );


        QMessageBox::information(

            this,

            "Simulacao concluida",

            "A simulacao foi executada com sucesso.\n\n"
            "Os resultados estao disponiveis nas abas "
            "Resultados e Graficos."
        );
    }


    catch (
        const std::exception& erro
    ) {

        labelStatusSimulacao->setText(
            "Status: erro durante a simulacao."
        );


        QMessageBox::critical(

            this,

            "Erro na simulacao",

            QString(
                "Nao foi possivel concluir a simulacao.\n\nErro: "
            )
            +
            QString::fromStdString(
                erro.what()
            )
        );
    }
}


// ==========================================================
// ABA 4 - RESULTADOS
// ==========================================================

void MainWindow::criarAbaResultados()
{

    QWidget* pagina =
        new QWidget();


    QVBoxLayout* layout =
        new QVBoxLayout(
            pagina
        );


    QLabel* titulo =
        new QLabel(
            "Resultados da Simulacao"
        );


    QFont fonte =
        titulo->font();


    fonte.setPointSize(
        14
    );


    fonte.setBold(
        true
    );


    titulo->setFont(
        fonte
    );


    layout->addWidget(
        titulo
    );


    QLabel* descricao =
        new QLabel(
            "Resultados petrofisicos, de geopressoes, "
            "fratura e janela operacional por camada."
        );


    descricao->setWordWrap(
        true
    );


    layout->addWidget(
        descricao
    );


    labelResumoResultados =
        new QLabel(
            "Execute a simulacao para visualizar os resultados."
        );


    labelResumoResultados->setWordWrap(
        true
    );


    layout->addWidget(
        labelResumoResultados
    );


    tabelaResultados =
        new QTableWidget();


    tabelaResultados->setColumnCount(
        10
    );


    tabelaResultados->setHorizontalHeaderLabels(

        QStringList()

            << "Indice"

            << "Tipo"

            << "Prof. media (m)"

            << "Delta t (us/ft)"

            << "Porosidade"

            << "Densidade (g/cm3)"

            << "Sigma v (psi)"

            << "Gp (lb/gal)"

            << "Gf (lb/gal)"

            << "Janela (lb/gal)"
    );


    tabelaResultados->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );


    tabelaResultados->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );


    tabelaResultados->setSelectionMode(
        QAbstractItemView::SingleSelection
    );


    tabelaResultados->setAlternatingRowColors(
        true
    );


    tabelaResultados
        ->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::ResizeToContents
        );


    tabelaResultados
        ->horizontalHeader()
        ->setStretchLastSection(
            true
        );


    layout->addWidget(
        tabelaResultados
    );


    botaoExportarResultados =
        new QPushButton(
            "Exportar resultados completos CSV"
        );


    layout->addWidget(
        botaoExportarResultados
    );


    connect(

        botaoExportarResultados,

        &QPushButton::clicked,

        this,

        &MainWindow::exportarResultadosInterface
    );


    abas->addTab(
        pagina,
        "Resultados"
    );
}


// ==========================================================
// ATUALIZAR TABELA
// ==========================================================

void MainWindow::atualizarTabelaResultados()
{

    if (
        tabelaResultados == nullptr
    ) {

        return;
    }


    const auto& camadas =
        simulador
            .getPoco()
            .getCamadas();


    tabelaResultados->setRowCount(
        static_cast<int>(
            camadas.size()
        )
    );


    auto textoValor =
        [](
            double valor,
            int casas
        ) -> QString {

            if (
                !std::isfinite(
                    valor
                )
            ) {

                return "-";
            }


            return QString::number(
                valor,
                'f',
                casas
            );
        };


    for (
        int linha = 0;
        linha < static_cast<int>(camadas.size());
        ++linha
    ) {

        const Camada& camada =
            camadas[
                static_cast<std::size_t>(
                    linha
                )
            ];


        const double gp =
            camada.getGradientePoro();


        const double gf =
            camada.getGradienteFratura();


        double larguraJanela =
            std::numeric_limits<double>::
            quiet_NaN();


        if (
            std::isfinite(gp)
            &&
            std::isfinite(gf)
            &&
            gf > gp
        ) {

            larguraJanela =
                gf - gp;
        }


        tabelaResultados->setItem(

            linha,

            0,

            new QTableWidgetItem(
                QString::number(
                    camada.getIndice()
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            1,

            new QTableWidgetItem(
                QString::fromStdString(
                    camada.getTipoTexto()
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            2,

            new QTableWidgetItem(
                textoValor(
                    camada.getProfundidadeMedia(),
                    3
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            3,

            new QTableWidgetItem(
                textoValor(
                    camada.getDeltaT(),
                    3
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            4,

            new QTableWidgetItem(
                textoValor(
                    camada.getPorosidade(),
                    4
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            5,

            new QTableWidgetItem(
                textoValor(
                    camada.getDensidadeBulk(),
                    4
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            6,

            new QTableWidgetItem(
                textoValor(
                    camada.getTensaoSobrecarga(),
                    2
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            7,

            new QTableWidgetItem(
                textoValor(
                    gp,
                    6
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            8,

            new QTableWidgetItem(
                textoValor(
                    gf,
                    6
                )
            )
        );


        tabelaResultados->setItem(

            linha,

            9,

            new QTableWidgetItem(
                textoValor(
                    larguraJanela,
                    6
                )
            )
        );
    }


    const Resultados& resultados =
        simulador.getResultados();


    labelResumoResultados->setText(

        "Camadas processadas: "
        +
        QString::number(
            static_cast<int>(
                camadas.size()
            )
        )
        +
        "    |    Janelas operacionais validas: "
        +
        QString::number(
            static_cast<int>(
                resultados
                    .obterJanelas()
                    .size()
            )
        )
        +
        "    |    ECD calculada: "
        +
        QString::number(
            resultados.getECDCalculada(),
            'f',
            6
        )
        +
        " lb/gal"
    );
}


// ==========================================================
// EXPORTAR RESULTADOS
// ==========================================================

void MainWindow::exportarResultadosInterface()
{

    if (
        !simulador
            .getResultados()
            .getSimulacaoValida()
    ) {

        QMessageBox::warning(

            this,

            "Simulacao nao executada",

            "Execute a simulacao antes de exportar os resultados."
        );


        return;
    }


    const QString caminhoArquivo =
        QFileDialog::getSaveFileName(

            this,

            "Exportar resultados completos",

            "resultados_completos.csv",

            "Arquivos CSV (*.csv)"
        );


    if (
        caminhoArquivo.isEmpty()
    ) {

        return;
    }


    const bool exportado =
        simulador
            .getResultados()
            .exportarDadosCompletos(

                simulador.getPoco(),

                simulador.getParametros(),

                caminhoArquivo.toStdString()
            );


    if (
        exportado
    ) {

        QMessageBox::information(

            this,

            "Exportacao concluida",

            "Os resultados foram exportados com sucesso."
        );
    }
    else {

        QMessageBox::critical(

            this,

            "Erro na exportacao",

            "Nao foi possivel salvar o arquivo de resultados."
        );
    }
}


// ==========================================================
// ABA 5 - GRÁFICOS
// ==========================================================

void MainWindow::criarAbaGraficos()
{

    QWidget* pagina =
        new QWidget();


    QVBoxLayout* layout =
        new QVBoxLayout(
            pagina
        );


    QLabel* titulo =
        new QLabel(
            "Graficos da Simulacao"
        );


    QFont fonte =
        titulo->font();


    fonte.setPointSize(
        14
    );


    fonte.setBold(
        true
    );


    titulo->setFont(
        fonte
    );


    layout->addWidget(
        titulo
    );


    QLabel* descricao =
        new QLabel(
            "Gere os graficos apos executar a simulacao. "
            "Utilize a lista abaixo para navegar entre os resultados."
        );


    descricao->setWordWrap(
        true
    );


    layout->addWidget(
        descricao
    );


    // ======================================================
    // BOTÃO GERAR
    // ======================================================

    botaoGerarGraficos =
        new QPushButton(
            "Gerar / Atualizar Graficos"
        );


    QFont fonteBotao =
        botaoGerarGraficos->font();


    fonteBotao.setBold(
        true
    );


    botaoGerarGraficos->setFont(
        fonteBotao
    );


    botaoGerarGraficos->setMinimumHeight(
        38
    );


    layout->addWidget(
        botaoGerarGraficos
    );


    // ======================================================
    // STATUS
    // ======================================================

    labelStatusGraficos =
        new QLabel(
            "Status: execute a simulacao antes de gerar os graficos."
        );


    labelStatusGraficos->setWordWrap(
        true
    );


    layout->addWidget(
        labelStatusGraficos
    );


    // ======================================================
    // SELETOR
    // ======================================================

    comboGraficos =
        new QComboBox();


    comboGraficos->setEnabled(
        false
    );


    comboGraficos->addItem(
        "Nenhum grafico gerado."
    );


    layout->addWidget(
        comboGraficos
    );


    // ======================================================
    // VISUALIZAÇÃO
    // ======================================================

    areaVisualizacaoGrafico =
        new QScrollArea();


    areaVisualizacaoGrafico->setWidgetResizable(
        true
    );


    areaVisualizacaoGrafico->setMinimumHeight(
        450
    );


    labelImagemGrafico =
        new QLabel(
            "Execute a simulacao e gere os graficos "
            "para visualiza-los aqui."
        );


    labelImagemGrafico->setAlignment(
        Qt::AlignCenter
    );


    labelImagemGrafico->setWordWrap(
        true
    );


    areaVisualizacaoGrafico->setWidget(
        labelImagemGrafico
    );


    layout->addWidget(
        areaVisualizacaoGrafico
    );


    // ======================================================
    // CONEXÕES
    // ======================================================

    connect(

        botaoGerarGraficos,

        &QPushButton::clicked,

        this,

        &MainWindow::gerarGraficosInterface
    );


    connect(

        comboGraficos,

        &QComboBox::currentIndexChanged,

        this,

        [this](int) {

            exibirGraficoSelecionado();
        }
    );


    abas->addTab(
        pagina,
        "Graficos"
    );
}


// ==========================================================
// LIMPAR GRÁFICOS ANTIGOS
// ==========================================================

void MainWindow::limparGraficosInterface()
{

    if (
        comboGraficos != nullptr
    ) {

        comboGraficos->clear();


        comboGraficos->addItem(
            "Nenhum grafico gerado."
        );


        comboGraficos->setEnabled(
            false
        );
    }


    if (
        labelImagemGrafico != nullptr
    ) {

        labelImagemGrafico->clear();


        labelImagemGrafico->setText(
            "Execute a simulacao e gere os graficos "
            "para visualiza-los aqui."
        );
    }


    if (
        labelStatusGraficos != nullptr
    ) {

        labelStatusGraficos->setText(
            "Status: graficos ainda nao gerados."
        );
    }
}


// ==========================================================
// GERAR GRÁFICOS
// ==========================================================

void MainWindow::gerarGraficosInterface()
{

    if (
        !simulador
            .getResultados()
            .getSimulacaoValida()
    ) {

        QMessageBox::warning(

            this,

            "Simulacao nao executada",

            "Execute primeiro a simulacao na aba ECD."
        );


        abas->setCurrentIndex(
            2
        );


        return;
    }


    // ======================================================
    // DIRETÓRIO TEMPORÁRIO
    // ======================================================

    const QString diretorioGraficos =
        QDir(
            QDir::tempPath()
        )
        .filePath(
            "SimuladorJanelaOperacional/graficos"
        );


    if (
        !QDir().mkpath(
            diretorioGraficos
        )
    ) {

        QMessageBox::critical(

            this,

            "Erro",

            "Nao foi possivel criar o diretorio dos graficos."
        );


        return;
    }


    labelStatusGraficos->setText(
        "Status: gerando graficos..."
    );


    QApplication::setOverrideCursor(
        Qt::WaitCursor
    );


    QApplication::processEvents();


    bool gerados =
        false;


    try {

        gerados =
            simulador
                .getResultados()
                .gerarGraficos(

                    simulador.getPoco(),

                    simulador.getParametros(),

                    diretorioGraficos.toStdString()
                );
    }


    catch (
        const std::exception& erro
    ) {

        QApplication::restoreOverrideCursor();


        labelStatusGraficos->setText(
            "Status: erro ao gerar graficos."
        );


        QMessageBox::critical(

            this,

            "Erro ao gerar graficos",

            QString(
                "Ocorreu um erro durante a geracao dos graficos.\n\nErro: "
            )
            +
            QString::fromStdString(
                erro.what()
            )
        );


        return;
    }


    QApplication::restoreOverrideCursor();


    if (
        !gerados
    ) {

        labelStatusGraficos->setText(
            "Status: nao foi possivel gerar os graficos."
        );


        QMessageBox::critical(

            this,

            "Erro ao gerar graficos",

            "Nao foi possivel executar a geracao dos graficos.\n\n"
            "Verifique se o Gnuplot esta instalado e disponivel no PATH."
        );


        return;
    }


    // ======================================================
    // PREENCHE A LISTA DE GRÁFICOS
    // ======================================================

    comboGraficos->clear();


    int quantidadeEncontrada =
        0;


    auto adicionarGrafico =
        [&](

            const QString& titulo,

            const QString& nomeArquivo

        ) {

            const QString caminhoCompleto =
                QDir(
                    diretorioGraficos
                )
                .filePath(
                    nomeArquivo
                );


            if (
                QFileInfo::exists(
                    caminhoCompleto
                )
            ) {

                comboGraficos->addItem(

                    titulo,

                    caminhoCompleto
                );


                ++quantidadeEncontrada;
            }
        };


    adicionarGrafico(

        "1 - Perfil Sonico e Tendencia Normal",

        "01_perfil_sonico_tendencia.png"
    );


    adicionarGrafico(

        "2 - Porosidade e Densidade",

        "02_porosidade_densidade.png"
    );


    adicionarGrafico(

        "3 - Tensao de Sobrecarga",

        "03_tensao_sobrecarga.png"
    );


    adicionarGrafico(

        "4 - Janela Operacional de Perfuracao",

        "04_janela_operacional.png"
    );


    adicionarGrafico(

        "5 - Comparacao dos Gradientes de Pressao",

        "05_gradientes_psi_ft.png"
    );


    adicionarGrafico(

        "6 - Limites Operacionais de Densidade de Lama",

        "06_mud_weight_operational_envelope.png"
    );


    adicionarGrafico(

        "7 - ECD na Janela Operacional",

        "07_ecd_operational_envelope.png"
    );


    if (
        quantidadeEncontrada == 0
    ) {

        comboGraficos->addItem(
            "Nenhum grafico encontrado."
        );


        comboGraficos->setEnabled(
            false
        );


        labelStatusGraficos->setText(
            "Status: arquivos de imagem nao encontrados."
        );


        QMessageBox::warning(

            this,

            "Graficos nao encontrados",

            "O Gnuplot foi executado, mas nenhum arquivo PNG "
            "foi encontrado."
        );


        return;
    }


    comboGraficos->setEnabled(
        true
    );


    comboGraficos->setCurrentIndex(
        0
    );


    exibirGraficoSelecionado();


    labelStatusGraficos->setText(

        "Status: "
        +
        QString::number(
            quantidadeEncontrada
        )
        +
        " graficos gerados com sucesso."
    );


    QMessageBox::information(

        this,

        "Graficos gerados",

        QString::number(
            quantidadeEncontrada
        )
        +
        " graficos foram gerados com sucesso."
    );
}


// ==========================================================
// EXIBIR GRÁFICO SELECIONADO
// ==========================================================

void MainWindow::exibirGraficoSelecionado()
{

    if (
        comboGraficos == nullptr
        ||
        !comboGraficos->isEnabled()
    ) {

        return;
    }


    const QString caminhoArquivo =
        comboGraficos
            ->currentData()
            .toString();


    if (
        caminhoArquivo.isEmpty()
    ) {

        return;
    }


    QPixmap imagem(
        caminhoArquivo
    );


    if (
        imagem.isNull()
    ) {

        labelImagemGrafico->setText(
            "Nao foi possivel carregar a imagem selecionada."
        );


        return;
    }


    // ======================================================
    // TAMANHO DISPONÍVEL NA ÁREA
    // ======================================================

    QSize tamanhoDisponivel =
        areaVisualizacaoGrafico
            ->viewport()
            ->size();


    tamanhoDisponivel.setWidth(

        tamanhoDisponivel.width()
        -
        20
    );


    tamanhoDisponivel.setHeight(

        tamanhoDisponivel.height()
        -
        20
    );


    if (
        tamanhoDisponivel.width() < 500
        ||
        tamanhoDisponivel.height() < 300
    ) {

        tamanhoDisponivel =
            QSize(
                1050,
                550
            );
    }


    const QPixmap imagemRedimensionada =
        imagem.scaled(

            tamanhoDisponivel,

            Qt::KeepAspectRatio,

            Qt::SmoothTransformation
        );


    labelImagemGrafico->setPixmap(
        imagemRedimensionada
    );


    labelImagemGrafico->setAlignment(
        Qt::AlignCenter
    );
}