#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent){
    resize(1050, 700); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    prepareMainWindow();

    //Connessioni tra segnali e slots delle classi
    connect(search, &SearchView::search_event, previews, &ItemView::submitQuery);
    connect(buttons, &MainButtonView::save_event, this, &MainWindow::save);
    connect(buttons, &MainButtonView::reload_event, this, &MainWindow::reload);
    connect(this, &MainWindow::reload_preview_event, previews, &ItemView::reload_preview);
} 

void MainWindow::prepareMainWindow(){
    mainLayout = new QHBoxLayout(this);
    previews = new ItemView();
    statistics = new StatView();
    search = new SearchView();
    buttons = new MainButtonView();

    mainLayout -> addWidget(previews);
    prepareMainRightWindow();
    mainLayout -> addWidget(right);
}

void MainWindow::prepareMainRightWindow(){
    right = new QWidget();
    right -> setMaximumWidth(330);
    QVBoxLayout* rightLayout = new QVBoxLayout(right);
    rightLayout -> addWidget(statistics);
    rightLayout -> addWidget(search);
    rightLayout -> addWidget(buttons);
}

/*save - slot per il savataggio*/
void MainWindow::save(){
    biblioteca::instance().save();
    QMessageBox info;
    info.setText("La biblioteca è stata salvata sul file!");
    info.exec();
}

void MainWindow::reload(){
    QMessageBox alert;
    QMessageBox info;
    info.setText("La biblioteca non è stata ricaricata!");
    alert.setText("Vuoi ricaricare la biblioteca?");
    alert.setInformativeText("La biblioteca verrà ripristinata all'ultimo salvataggio.");
    alert.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
    alert.setDefaultButton(QMessageBox::Apply);
    int ret = alert.exec();
    switch (ret){
        case QMessageBox::Apply:
            biblioteca::instance().load();
            emit(reload_preview_event());
            break;
        case QMessageBox::Cancel:
            info.exec();
            break;
        default:
            break;
    }
}

void MainWindow::show_full_preview(int ip){

}