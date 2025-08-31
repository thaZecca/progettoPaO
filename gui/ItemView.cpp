#include "include/ItemView.hpp"

ItemView::ItemView(QWidget* parent): QScrollArea(parent){
    PreviewVisitor prevVisitor; //visitor che crea la preview per ogni item
    setWidgetResizable(true); //ridimensionamento automatico
    QWidget* previews = new QWidget(); //QWidget che contiene tutte le preview
    QVBoxLayout* previewLayout = new QVBoxLayout(previews); //layout per il widget totale
    //aggiungo al layout ogni preview di contenutoMultimediale
    for(auto& c : biblioteca::instance().getContenuti()){
        c -> accept(prevVisitor);
        previewLayout -> addWidget(prevVisitor.getPreview());
    }
    for(auto& s : biblioteca::instance().getSupporti()){
        s -> accept(prevVisitor);
        previewLayout -> addWidget(prevVisitor.getPreview());
    }
    previewLayout -> addStretch(); //stretcho il layout totale
    setWidget(previews); //aggiungo il widget delle previews alla scrollbar area
}
