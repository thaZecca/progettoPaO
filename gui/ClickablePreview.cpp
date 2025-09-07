#include "include/ClickablePreview.hpp"

/*Costruttore parametrico di ClickablePreview
@param parent*/
ClickablePreview::ClickablePreview(QWidget* parent): QWidget(parent){}

/*mousePressEvent - creo l'evento di click sui widget che rappresentano una preview
#parma event*/
void ClickablePreview::mousePressEvent(QMouseEvent* event){
    emit(clicked(objectName().toInt()));
    QWidget::mousePressEvent(event);
}