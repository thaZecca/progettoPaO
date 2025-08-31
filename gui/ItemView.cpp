#include "include/ItemView.hpp"

ItemView::ItemView(QWidget* parent): QWidget(parent){
    PreviewVisitor prevVisitor;
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea -> setWidgetResizable(true); //ridimensionamento automatico
    QWidget* previews = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(previews);
    for(auto& c : biblioteca::instance().getContenuti()){
        c -> accept(prevVisitor);
        mainLayout -> addWidget(prevVisitor.getPreview());
    }
    scrollArea->setWidget(previews);
}
