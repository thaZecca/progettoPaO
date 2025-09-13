#include "include/AddSupportoView.hpp"

/*Costruttore parametrico di classe AddSupportoView
@param parent QWidget parent*/
AddSupportoView::AddSupportoView(QWidget* parent): QWidget(parent), aC(nullptr), ti(nullptr), s(nullptr), trc(nullptr), di(nullptr), titolo(nullptr), scaffale(nullptr), diametro(nullptr), tipo(nullptr), add(nullptr), cancel(nullptr), save(nullptr), areaTracce(nullptr){
    mainLayout = new QVBoxLayout(this);
    scrollTracce = new QScrollArea(this);
    scrollTracce -> setWidgetResizable(true);
    prepare();
    layoutScrollable = new QVBoxLayout(areaTracce);
    scrollTracce -> setWidget(areaTracce);
    connect(cancel, &QPushButton::clicked, this, &AddSupportoView::cancel_event);
    connect(add, &QPushButton::clicked, this, &AddSupportoView::addTracce);
    connect(tipo, &QButtonGroup::buttonClicked, this, &AddSupportoView::cambioTipo); //evito supporti con contenuti misti
    connect(save, &QPushButton::clicked, this, &AddSupportoView::salva);
}

/*prepare - metodo che prepara l'interfaccia grafica*/
void AddSupportoView::prepare(){
    QHBoxLayout* etichetteLayout = new QHBoxLayout();
    if(ti==nullptr) ti = new QLabel("Titolo:");
    etichetteLayout -> addWidget(ti);
    if(titolo==nullptr) titolo = new QLineEdit();
    etichetteLayout -> addWidget(titolo);

    if(s==nullptr) s = new QLabel("Scaffale:");
    etichetteLayout -> addWidget(s);
    if(scaffale==nullptr) scaffale = new QLineEdit();
    etichetteLayout -> addWidget(scaffale);

    if(di==nullptr) di = new QLabel("Diametro:");
    etichetteLayout -> addWidget(di);
    if(diametro==nullptr) diametro = new QSpinBox();
    etichetteLayout -> addWidget(diametro);


    mainLayout -> addLayout(etichetteLayout);

    QHBoxLayout* tipoLayout = new QHBoxLayout();
    if(c==nullptr) c = new QRadioButton("CD");
    tipoLayout -> addWidget(c);

    if(d==nullptr) d = new QRadioButton("DVD");
    tipoLayout -> addWidget(d);

    if(tipo==nullptr){
        tipo = new QButtonGroup();
        tipo -> addButton(c);
        tipo -> addButton(d);
    } 

    mainLayout -> addLayout(tipoLayout);

    QHBoxLayout* addTracceLayout = new QHBoxLayout();
    if(trc == nullptr) trc = new QLabel("Tracce:");
    addTracceLayout -> addWidget(trc);
    if(add==nullptr) add = new QPushButton("+");
    addTracceLayout -> addWidget(add);
    mainLayout -> addLayout(addTracceLayout);

    if(cancel==nullptr) cancel = new QPushButton("Cancella");
    if(save==nullptr) save = new QPushButton("Salva");

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout -> addWidget(cancel);
    buttonsLayout -> addWidget(save);

    prepareScrollable();
    mainLayout -> addWidget(scrollTracce);

    mainLayout -> addLayout(buttonsLayout, Qt::AlignBottom | Qt::AlignCenter);

}

/*prepareScrollable - prepara l'area scrollabile con i contenuti aggiunti al supporto*/
void AddSupportoView::prepareScrollable(){
    PreviewVisitor v;
    saveLayout(layoutScrollable);
    if(areaTracce==nullptr) areaTracce = new QWidget();
    for(auto it = tracce.begin(); it != tracce.end(); it++){
        (*it) -> accept(v);
        layoutScrollable -> addWidget(v.getPreview());
    }
}

/*addTracce - slot che cattura il segnale del pulsante di aggiunta traccia
@ref AddContenutoView*/
void AddSupportoView::addTracce(){
    if(!tipo -> checkedButton()){
        error("Selezionare un tipo!");
    }else{
        saveLayout(mainLayout);

        int st = 0;
        if(tipo -> checkedButton() -> text() == "CD"){
            st = 1;
        }else{ //DVD
            st = 2;
        }

        aC = new AddContenutoView(st);
        mainLayout -> addWidget(aC);

        connect(aC, &AddContenutoView::cancel_event, this, &AddSupportoView::addTracce_cancel);
        connect(aC, &AddContenutoView::return_save_event, this, &AddSupportoView::addTracce_save);
    }
}

/*addTracce_cancel - slot che riceve il segnale dal tasto cancella durante l'aggiunta delle tracce*/
void AddSupportoView::addTracce_cancel(){
    saveLayout(mainLayout);
    prepare();
}

/*error - mostra i messaggi di errore all'utente
@param m stringa con il messaggio da mostrare all'untente*/
void AddSupportoView::error(QString m){
    QMessageBox info;
    info.setText(m);
    info.exec();
}

/*addTracce_save - slot che riceve il segnale di salvataggio quando si creano le tracce*/
void AddSupportoView::addTracce_save(){
    tracce.push_back(aC -> getContenuto());
    addTracce_cancel();
}

/*saveLayout - svuota il layout ma salva i widget contenuti in esso. 
@warning i sottolayout vengono eliminati
@param layout da "salvare"*/
void AddSupportoView::saveLayout(QLayout* layout) {
    if (!layout) return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->setParent(nullptr); //stacca i widget dal layout
        } else if (item->layout()) {
            saveLayout(item->layout()); //ricorsivo per layout annidati
            item->layout()->deleteLater(); //elimina layouts e sottolayouts
        }
        delete item; //elimina l'item stesso
    }
}

/*cambio tipo - elimino il contenuto del CD/DVD al cambio di tipo di supporto in quanto non esistono supporti di tipo misto*/
void AddSupportoView::cambioTipo(){
    for(auto it = tracce.begin(); it != tracce.end();){
        tracce.erase(it);
    }
    prepareScrollable();
}

/*salva - slot che riceve il segnale di salvataggio dal tasto salva. Permette di salvare il supporto nella biblioteca.*/
void AddSupportoView::salva(){
    if(!titolo -> text().isEmpty() && !scaffale -> text().isEmpty() && tipo -> checkedButton()){
        if(tipo -> checkedButton() -> text() == "CD"){
            vector<audioD*> tA;
            for(auto t : tracce) tA.push_back(static_cast<audioD*>(t));
            biblioteca::add(new cd(tA, diametro -> value(), scaffale -> text(), titolo -> text()));
        }else{ //DVD
            vector<videoD*> tV;
            for(auto t : tracce) tV.push_back(static_cast<videoD*>(t));
            biblioteca::add(new dvd(tV, diametro -> value(),scaffale -> text(), titolo -> text()));
        }
        emit(cancel_event());
    }else{
        error("Uno o più campi incompleti o errati!");
    }
    
}