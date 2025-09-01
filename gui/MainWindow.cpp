#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent){
    resize(900, 650); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    ItemView* previews = new ItemView();
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout -> addWidget(previews);
} 