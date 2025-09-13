#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent), mainLayout(nullptr), right(nullptr), previews(nullptr), statistics(nullptr), search(nullptr), buttons(nullptr), fullprev(nullptr), status(nullptr), remove_activated(false){
    resize(1050, 700); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    mainLayout = new QHBoxLayout(this);
    prepareMainWindow();
} 

/*prepareMainWindow - prepara la finestra principale di default*/
void MainWindow::prepareMainWindow(){
    if(right){
        right -> deleteLater(); //situazione delicata 
        right = nullptr;
    }
    if(previews){
        previews -> deleteLater(); //situazione delicata
        previews = nullptr;
    }
    previews = new ItemView();

    mainLayout -> addWidget(previews);
    prepareMainRightWindow();

    //Connessione tra segnali e slots delle classi
    connect(previews, &ItemView::clicked, this, &MainWindow::dispatcher);
}

/*prepareMainWindow - prepara nella finestra principale la schermata destra di default */
void MainWindow::prepareMainRightWindow(){
    statistics = new StatView();
    search = new SearchView();
    buttons = new MainButtonView();
    right = new QWidget();
    right -> setMaximumWidth(330);
    status = new QLabel((remove_activated?"Rimozione attivata!":""));
    QVBoxLayout* rightLayout = new QVBoxLayout(right);
    rightLayout -> addWidget(statistics);
    rightLayout -> addWidget(search);
    rightLayout -> addWidget(buttons);
    rightLayout -> addWidget(status);
    mainLayout -> addWidget(right);

    //Connessioni tra segnali e slots delle classi
    connect(search, &SearchView::search_event, previews, &ItemView::submitQuery);
    connect(buttons, &MainButtonView::save_event, this, &MainWindow::save);
    connect(buttons, &MainButtonView::reload_event, this, &MainWindow::reload);
    connect(this, &MainWindow::reload_preview_event, previews, &ItemView::reload_preview);
    connect(buttons, &MainButtonView::add_event, this, &MainWindow::add_object);
    connect(buttons, &MainButtonView::remove_event, this, &MainWindow::set_remove);
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
            prepareMainWindow();
            break;
        case QMessageBox::Cancel:
            info.exec();
            break;
        default:
            break;
    }
}

/*dispatcher - slot che smista il segnale di click sulla clickable previe a seconda se remove è stato attivato.
@param ip index position dell'oggetto cliccato*/
void MainWindow::dispatcher(int ip){
    if(remove_activated){
        remove(ip);
    }else{
        show_full_preview(ip);
    }
}

/*show_full_preview - mostra la fullpreview
@param ip index position dell'oggetto cliccato*/
void MainWindow::show_full_preview(int ip){
    if(right){
        right -> deleteLater();
        right = nullptr;
    }
    if(fullprev){ 
        fullprev -> deleteLater();
        fullprev = nullptr;
    }
    fullprev = new FullPreview(ip, previews->getLastQuery());
    mainLayout -> addWidget(fullprev);
    connect(fullprev, &FullPreview::back_event, this, &MainWindow::back);
}

/*add_back - slot che riceve il segnale di "back" (o indietro) dalla fullpreview e ricostruisce l'interfaccia di default*/
void MainWindow::back(){
    fullprev -> deleteLater();
    fullprev = nullptr;
    prepareMainRightWindow();
}

/*add_object - slot che riceve il segnale per aggiungere un oggetto alla biblioteca*/
void MainWindow::add_object(){
    right -> deleteLater();
    right = nullptr;
    previews -> deleteLater();
    previews = nullptr;
    addobject = new AddObjectView();
    mainLayout -> addWidget(addobject);
    
    connect(addobject, &AddObjectView::back_event, this, &MainWindow::add_back);
}

/*add_back - slot che riceve il segnale di "back" (o indietro) dalla pagina add e ricostruisce l'interfaccia di default*/
void MainWindow::add_back(){
    addobject -> deleteLater(); //situazione delicata
    addobject = nullptr; //evito dangling reference
    prepareMainWindow();
}

/*set_remove - riceve il segnale dal tasto remove e attiva la funzionalità di rimozione*/
void MainWindow::set_remove(){
    remove_activated = !remove_activated;
    status -> setText((remove_activated?"Rimozione attivata!":""));
}

/*remove - rimuove l'oggetto cliccato
@param ip index position dell'oggetto da eliminare*/
void MainWindow::remove(int ip){
    QMessageBox info;
    info.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    info.setText("Sei sicuro di volerlo cancellare?");
    int ret = info.exec();
    QMessageBox discard_info;

    switch(ret){
        case QMessageBox::Yes:
            biblioteca::instance().remove(ip, previews -> getLastQuery());
            prepareMainWindow();
            break;
        case QMessageBox::No:
            discard_info.setText("La biblioteca non è stata modificata!");
            discard_info.exec();
            break;
        default:
            break;
    }
}