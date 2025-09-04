#include "include/ItemView.hpp"

/*Costruttore parametrico
@param parent*/
ItemView::ItemView(QWidget* parent): QScrollArea(parent){
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

    //aggiungo al layout ogni preview di contenutoMultimediale
    for(auto c = con.begin(); c != con.end(); c++){
        (*c) -> accept(v);
        previewLayout -> addWidget(v.getPreview());
    }
    for(auto s = sup.begin(); s != sup.end(); s++){
        (*s) -> accept(v);
        previewLayout -> addWidget(v.getPreview());
    }
    previewLayout -> addStretch(); //stretcho il layout totale
    setWidget(previews);
}

/*submitQuery - slot che ridireziona la query
@param q query*/
void ItemView::submitQuery(query q){
    prepare(&q);
}

/*reload_preview - slot per ricaricare l'interfaccia a seguito di ricaricamenti dal file di storage*/
void ItemView::reload_preview(){
    prepare();
}
