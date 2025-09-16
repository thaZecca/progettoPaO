#include <QApplication>
#include "./gui/include/MainWindow.hpp"
#include "fileManager/include/biblioteca.hpp"

int main(int argc, char* argv[]){
    #if defined(Q_OS_MAC) //direttiva per sistema operativo Apple macOS
        qputenv("QT_QPA_PLATFORM", "cocoa");
    #else
        qputenv("QT_QPA_PLATFORM", "wayland"); //per evitare warning a causa dell'ambiente grafico 
    #endif
    QApplication app(argc,argv);

    MainWindow mw;
    mw.setWindowTitle("Biblioteca");
    mw.show();

    return app.exec();
}