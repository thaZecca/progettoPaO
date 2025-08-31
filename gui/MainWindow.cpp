#include "include/MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    resize(900, 650); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    PreviewVisitor v;
    (*(biblioteca::instance().getContenuti().begin())) -> accept(v);
    prova = v.getPreview();
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout -> addWidget(prova);
} 