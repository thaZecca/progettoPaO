#include "include/MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    resize(900, 650); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
} 