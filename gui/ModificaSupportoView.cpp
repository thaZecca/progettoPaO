#include "include/ModificaSupportoView.hpp"

/*Costruttore parametrico di Modifica SupportoView
@param s puntatore al supportoMultimediale da modificare
@param parent QWidget parent*/
ModificaSupportoView::ModificaSupportoView(supportoMultimediale* s, QWidget* parent): QWidget(parent), ptr(s), ti(nullptr), s(nullptr), trc(nullptr), di(nullptr), titolo(nullptr), scaffale(nullptr), diametro(nullptr), avvisoRimozione(nullptr), rimozione(nullptr), add(nullptr), cancel(nullptr), save(nullptr), areaTracce(nullptr), rimozione_attiva(false){
    mainLayout = new QVBoxLayout(this);
    tracce = ptr -> getTracce();
    scrollTracce = new QScrollArea(this);
    scrollTracce -> setWidgetResizable(true);
    areaTracce = new QWidget();
    layoutScrollable = new QVBoxLayout(areaTracce);
    prepare();
    
    scrollTracce -> setWidget(areaTracce);

    connect(add, &QPushButton::clicked, this, &ModificaSupportoView::addTracce);
    connect(rimozione, &QPushButton::clicked, this, &ModificaSupportoView::set_rimozione);
    connect(cancel, &QPushButton::clicked, this, &ModificaSupportoView::cancel_event);
    connect(save, &QPushButton::clicked, this, &ModificaSupportoView::salva);
}

/*prepare - metodo che prepara l'interfaccia grafica*/
void ModificaSupportoView::prepare(){
    QHBoxLayout* etichetteLayout = new QHBoxLayout();
    if(ti==nullptr) ti = new QLabel("Titolo:");
    etichetteLayout -> addWidget(ti);
    if(titolo==nullptr) titolo = new QLineEdit();
    titolo -> setText(ptr -> getTitolo());
    etichetteLayout -> addWidget(titolo);

    if(s==nullptr) s = new QLabel("Scaffale:");
    etichetteLayout -> addWidget(s);
    if(scaffale==nullptr) scaffale = new QLineEdit();
    scaffale -> setText(ptr -> getScaffale());
    etichetteLayout -> addWidget(scaffale);

    if(di==nullptr) di = new QLabel("Diametro:");
    etichetteLayout -> addWidget(di);
    if(diametro==nullptr) diametro = new QSpinBox();
    diametro -> setValue(ptr -> getDiametro());
    etichetteLayout -> addWidget(diametro);
    mainLayout -> addLayout(etichetteLayout);

    QHBoxLayout* addTracceLayout = new QHBoxLayout();
    if(trc == nullptr) trc = new QLabel("Tracce:");
    addTracceLayout -> addWidget(trc);
    if(add==nullptr) add = new QPushButton("+");
    if(rimozione==nullptr) rimozione = new QPushButton("-");
    addTracceLayout -> addWidget(add);
    addTracceLayout -> addWidget(rimozione);
    mainLayout -> addLayout(addTracceLayout);

    if(avvisoRimozione==nullptr) avvisoRimozione = new QLabel((rimozione_attiva?"Rimozione attivata!":""));
    mainLayout -> addWidget(avvisoRimozione);

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
void ModificaSupportoView::prepareScrollable(){
    PreviewVisitor v;
    AddSupportoView::saveLayout(layoutScrollable);
    if(areaTracce==nullptr) areaTracce = new QWidget();
    int count = 0;
    ClickablePreview* cp;
    for(auto t : tracce){
        t -> accept(v);
        cp = v.getPreview();
        cp -> setObjectName(QString::number(count));
        layoutScrollable -> addWidget(cp);
        count++;
        connect(cp, &ClickablePreview::clicked, this, &ModificaSupportoView::click_preview); //connetto tutte le preview ad un unico slot
    }
}

/*addTracce - slot che riceve il segnale dal pulsante per aggiungere tracce*/
void ModificaSupportoView::addTracce(){
    AddSupportoView::saveLayout(mainLayout);
    int s = 0;
    if(dynamic_cast<cd*>(ptr)) s = 1;
    else s = 2;

    aggiuntaTraccia = new AddContenutoView(s);
    mainLayout -> addWidget(aggiuntaTraccia);

    connect(aggiuntaTraccia, &AddContenutoView::cancel_event, this, &ModificaSupportoView::cancelTraccia);
    connect(aggiuntaTraccia, &AddContenutoView::return_save_event, this, &ModificaSupportoView::salvaTraccia);
}

/*set_rimozione - slot che imposta la modalità rimozione*/
void ModificaSupportoView::set_rimozione(){
    rimozione_attiva = !rimozione_attiva;
    avvisoRimozione -> setText(rimozione_attiva?"Rimozione attivata!":"");
}

/*cancelTraccia - slot che riceve il segnale di cancel dall'aggiunta tracce*/
void ModificaSupportoView::cancelTraccia(){
    aggiuntaTraccia -> deleteLater();
    aggiuntaTraccia = nullptr;
    prepare();
}

/*salvaTraccia - slot che riceve il segnale di salvataggio dall'aggiunta tracce*/
void ModificaSupportoView::salvaTraccia(){
    tracce.push_back(aggiuntaTraccia -> getContenuto());
    aggiuntaTraccia -> deleteLater();
    aggiuntaTraccia = nullptr;
    prepare();
}

/*click_preview - slot che riceve il segnale di click sulle preview delle tracce*/
void ModificaSupportoView::click_preview(int ip){
    if(rimozione_attiva){
        if(ip < static_cast<int>(ptr -> getTracce().size())){
            QMessageBox info;
            info.setText("Sei sicuro di voler eliminare il contenuto?");
            info.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int ret = info.exec();

            QMessageBox discardInfo;
            discardInfo.setText("Nessuna modifica effettuata!");

            switch(ret){
                case QMessageBox::Yes:
                    tracce.erase(tracce.begin()+ip);
                    prepareScrollable();
                    break;
                case QMessageBox::No:
                    discardInfo.exec();
                    break;
                default:
                    break;

            }
        }
    }
}

/*salva - slot che riceve il segnale di salvataggio delle modifiche*/
void ModificaSupportoView::salva(){
    if(!titolo -> text().isEmpty() && !scaffale -> text().isEmpty()){
        ptr -> setTitolo(titolo -> text());
        ptr -> setScaffale(scaffale -> text());
        ptr -> setDiametro(diametro -> value());
        ptr -> setTracce(tracce);
        emit(cancel_event());
    }else{
        QMessageBox error;
        error.setText("Uno o più campi vuoti!");
        error.exec();
    }
}