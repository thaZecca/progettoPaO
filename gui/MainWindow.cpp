#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent), mainLayout(nullptr), right(nullptr), previews(nullptr), statistics(nullptr), search(nullptr), buttons(nullptr), fullprev(nullptr){
    resize(1050, 700); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    mainLayout = new QHBoxLayout(this);
    prepareMainWindow();
} 

/*prepareMainWindow - prepara la finestra principale di default*/
void MainWindow::prepareMainWindow(){
    previews = new ItemView();

    mainLayout -> addWidget(previews);
    prepareMainRightWindow();

    //Connessione tra segnali e slots delle classi
    connect(previews, &ItemView::clicked, this, &MainWindow::show_full_preview);
}

/*prepareMainWindow - prepara nella finestra principale la schermata destra di default */
void MainWindow::prepareMainRightWindow(){
    statistics = new StatView();
    search = new SearchView();
    buttons = new MainButtonView();
    right = new QWidget();
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
    connect(buttons, &MainButtonView::add_event, this, &MainWindow::add_object);
}

/*save - slot per il savataggio*/
void MainWindow::save(){
    biblioteca::instance().save();
    QMessageBox info;
    info.setText("La biblioteca è stata salvata sul file!");
    info.exec();
}

/*reload - slot per ricevere il segnale di ricarica dal file*/
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

/*show_full_preview - slot per ricevere il segnale di mostrare la fullpreview
@param ip index position dell'oggetto cliccato*/
void MainWindow::show_full_preview(int ip){
    if(right){
        delete right;
        right = nullptr;
    }
    if(fullprev != nullptr){ 
        delete fullprev;
        fullprev = nullptr;
    }
    fullprev = new FullPreview(ip, previews->getLastQuery());
    mainLayout -> addWidget(fullprev);
    connect(fullprev, &FullPreview::back_event, this, &MainWindow::back);
}

void MainWindow::back(){
    delete fullprev;
    fullprev = nullptr;
    prepareMainRightWindow();
}

void MainWindow::add_object(){
    delete right;
    delete previews;
    addobject = new AddObjectView();
    mainLayout -> addWidget(addobject);
    
    connect(addobject, &AddObjectView::back_event, this, &MainWindow::add_back);
}

void MainWindow::add_back(){
    delete addobject;
    prepareMainWindow();
}