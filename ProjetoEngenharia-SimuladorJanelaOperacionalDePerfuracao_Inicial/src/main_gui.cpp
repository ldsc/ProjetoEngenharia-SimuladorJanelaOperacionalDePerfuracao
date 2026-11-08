#include "MainWindow.h"

#include <QApplication>


int main(
    int argc,
    char* argv[]
)
{

    QApplication aplicacao(
        argc,
        argv
    );


    MainWindow janela;


    janela.show();


    return
        aplicacao.exec();
}