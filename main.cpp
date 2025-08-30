#include <QApplication>
#include "./gui/include/MainWindow.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    MainWindow mw;
    mw.setWindowTitle("Prova Biblioteca");
    mw.show();

    return app.exec();
}