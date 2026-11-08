#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SimuladorJanelaOperacional.h"

#include <QMainWindow>


class QTabWidget;
class QLabel;
class QPushButton;
class QDoubleSpinBox;
class QTableWidget;
class QComboBox;
class QScrollArea;


class MainWindow : public QMainWindow {

    Q_OBJECT


private:

    // ======================================================
    // MOTOR DO SIMULADOR
    // ======================================================

    SimuladorJanelaOperacional simulador;


    // ======================================================
    // INTERFACE PRINCIPAL
    // ======================================================

    QTabWidget* abas;


    // ======================================================
    // ABA DADOS DO POÇO
    // ======================================================

    QLabel* labelArquivoPoco;

    QLabel* labelNumeroCamadas;

    QLabel* labelProfundidadeMaxima;

    QLabel* labelStatusDados;

    QPushButton* botaoSelecionarPoco;


    // ======================================================
    // ABA PARÂMETROS
    // ======================================================

    QLabel* labelArquivoParametros;

    QLabel* labelStatusParametros;

    QPushButton* botaoSelecionarParametros;

    QPushButton* botaoAplicarParametros;


    QDoubleSpinBox* campoDensidadeMatriz;

    QDoubleSpinBox* campoDensidadeFluido;

    QDoubleSpinBox* campoDensidadeAguaMar;

    QDoubleSpinBox* campoDensidadeSedimento;

    QDoubleSpinBox* campoDeltaTMatriz;

    QDoubleSpinBox* campoDeltaTFluido;

    QDoubleSpinBox* campoPorosidadeSedimento;

    QDoubleSpinBox* campoPorosidadeMinima;

    QDoubleSpinBox* campoPorosidadeMaxima;


    QDoubleSpinBox* campoGradienteHidrostatico;

    QDoubleSpinBox* campoExpoenteEaton;

    QDoubleSpinBox* campoCoeficientePoisson;

    QDoubleSpinBox* campoDeltaTReferencia;

    QDoubleSpinBox* campoConstanteCompactacao;


    // ======================================================
    // ABA ECD
    // ======================================================

    QDoubleSpinBox* campoDensidadeLamaECD;

    QDoubleSpinBox* campoPerdaPressaoECD;

    QDoubleSpinBox* campoProfundidadeECD;

    QPushButton* botaoExecutarSimulacao;

    QLabel* labelStatusSimulacao;

    QLabel* labelProfundidadeSolicitada;

    QLabel* labelProfundidadeAvaliada;

    QLabel* labelECDCalculada;

    QLabel* labelGradientePoroECD;

    QLabel* labelGradienteFraturaECD;

    QLabel* labelClassificacaoECD;


    // ======================================================
    // ABA RESULTADOS
    // ======================================================

    QLabel* labelResumoResultados;

    QTableWidget* tabelaResultados;

    QPushButton* botaoExportarResultados;


    // ======================================================
    // ABA GRÁFICOS
    // ======================================================

    QLabel* labelStatusGraficos;

    QPushButton* botaoGerarGraficos;

    QComboBox* comboGraficos;

    QScrollArea* areaVisualizacaoGrafico;

    QLabel* labelImagemGrafico;


    // ======================================================
    // CONSTRUÇÃO DA INTERFACE
    // ======================================================

    void criarInterface();

    void criarAbaDadosPoco();

    void criarAbaParametros();

    void criarAbaECD();

    void criarAbaResultados();

    void criarAbaGraficos();


    // ======================================================
    // DADOS / PARÂMETROS
    // ======================================================

    void selecionarArquivoPoco();

    void selecionarArquivoParametros();

    void aplicarParametrosInterface();

    void atualizarCamposParametros();


    // ======================================================
    // SIMULAÇÃO
    // ======================================================

    void executarSimulacaoInterface();


    // ======================================================
    // RESULTADOS
    // ======================================================

    void atualizarTabelaResultados();

    void exportarResultadosInterface();


    // ======================================================
    // GRÁFICOS
    // ======================================================

    void gerarGraficosInterface();

    void exibirGraficoSelecionado();

    void limparGraficosInterface();


public:

    explicit MainWindow(
        QWidget* parent = nullptr
    );


    ~MainWindow() override;
};


#endif