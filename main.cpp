#include <QApplication>
#include "./gui/include/MainWindow.hpp"
#include "fileManager/include/biblioteca.hpp"

int main(int argc, char* argv[]){
    qputenv("QT_QPA_PLATFORM", "xcb"); //per evitare warning a causa dell'ambiente grafico 
    QApplication app(argc,argv);

    MainWindow mw;
    mw.setWindowTitle("Biblioteca");
    mw.show();

    return app.exec();
}