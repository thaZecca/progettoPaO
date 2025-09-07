#include "include/ItemView.hpp"

/*Costruttore parametrico
@param parent*/
ItemView::ItemView(QWidget* parent): QScrollArea(parent), lastQuery(nullptr){
    setWidgetResizable(true); //ridimensionamento automatico
    prepare(); //preparo il widget delle previews nella scrollbar area
}

/*prepare - prepara l'interfaccia di item a seconda del visitor
@param v visitor*/
void ItemView::prepare(query* q){
    PreviewVisitor v; //visitor che crea la preview per ogni item
    setWidget(nullptr); //libera la memoria occupata dal vecchio widget

    QWidget* previews = new QWidget(); //QWidget che contiene tutte le preview
    QVBoxLayout* previewLayout = new QVBoxLayout(previews); //layout per il widget totale

    vector<contenutoMultimediale*> con = biblioteca::instance().getContenuti();
    vector<supportoMultimediale*> sup = biblioteca::instance().getSupporti();

    if(q) q -> filter(con,sup);

    ClickablePreview* p;

    //aggiungo al layout ogni preview di contenutoMultimediale
    int count = 0;
    for(auto c = con.begin(); c != con.end(); c++){
        (*c) -> accept(v);
        p = v.getPreview();
        p -> setObjectName(QString::number(count));
        previewLayout -> addWidget(p);
        count++;
        connect(p, &ClickablePreview::clicked, this, &ItemView::click_preview_event); //connetto tutte le preview ad un unico slot
    }
    for(auto s = sup.begin(); s != sup.end(); s++){
        (*s) -> accept(v);
        p = v.getPreview();
        p -> setObjectName(QString::number(count));
        previewLayout -> addWidget(p);
        count++;
        connect(p, &ClickablePreview::clicked, this, &ItemView::click_preview_event); //connetto tutte le preview ad un unico slot
    }
    previewLayout -> addStretch(); //stretcho il layout totale
    setWidget(previews);
}

/*getLastQuery
@return l'ultima query effettuata*/
query* ItemView::getLastQuery() const{
    return lastQuery;
}

/*submitQuery - slot che ridireziona la query
@param q query*/
void ItemView::submitQuery(query q){
    prepare(&q);
    delete lastQuery; //libero la memoria se è occupata
    lastQuery = new query(q); //creo una copia così non la perdo
}

/*reload_preview - slot per ricaricare l'interfaccia a seguito di ricaricamenti dal file di storage*/
void ItemView::reload_preview(){
    prepare();
}

/*click_preview_event - slot per ricevere l'evento di click sulle preview
@param ip indice della preview cliccata*/
void ItemView::click_preview_event(int ip){
    emit(clicked(ip));
}
