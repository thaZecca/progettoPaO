#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent){
    resize(1050, 700); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    ItemView* previews = new ItemView();
    StatView* statistics = new StatView();
    SearchView* search = new SearchView();
    MainButtonView* buttons = new MainButtonView();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout -> addWidget(previews);

    QWidget* right = new QWidget();
    right -> setMaximumWidth(330);
    QVBoxLayout* rightLayout = new QVBoxLayout(right);
    rightLayout -> addWidget(statistics);
    rightLayout -> addWidget(search);
    rightLayout -> addWidget(buttons);

    mainLayout -> addWidget(right);

    //Connessioni tra segnali e slots delle classi
    connect(search, &SearchView::search_event, previews, &ItemView::submitQuery);
    connect(buttons, &MainButtonView::save_event, this, &MainWindow::save);
    connect(buttons, &MainButtonView::reload_event, this, &MainWindow::reload);
    connect(this, &MainWindow::reload_preview_event, previews, &ItemView::reload_preview);
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