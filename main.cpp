#include <QApplication>
#include "./gui/include/MainWindow.hpp"
#include "fileManager/include/biblioteca.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    MainWindow mw;
    mw.setWindowTitle("Biblioteca");
    mw.show();

    return app.exec();
}