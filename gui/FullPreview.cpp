#include "include/FullPreview.hpp"

FullPreview::FullPreview(int ip, query* q, QWidget* parent): QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    prepare(ip,q);
    mainLayout -> addWidget(multimedia);
    
    back = new QPushButton("Indietro");
    modifica = new QPushButton("Modifica");

    mainLayout -> addWidget(back);
    mainLayout -> addWidget(modifica);
    setMinimumWidth(320);
    setMaximumWidth(320);

    connect(back, &QPushButton::clicked, this, &FullPreview::back_event);
}

/*prepare - prepara la fullpreview
@param ip index position dell'oggetto da mostrare
@param q ultima query eseguita*/
void FullPreview::prepare(int ip, query* q){
    vector<contenutoMultimediale*> c = biblioteca::instance().getContenuti();
    vector<supportoMultimediale*> s = biblioteca::instance().getSupporti();
    if(q) q -> filter(c,s);
    contenutoMultimediale* objC = biblioteca::cSearch(ip,c,s);
    supportoMultimediale* objS = biblioteca::sSearch(ip,c,s);

    FullPreviewVisitor v;

    if(objC){
        objC -> accept(v);
        multimedia = v.getFullPreview();
    }else{
        objS -> accept(v);
        multimedia = v.getFullPreview();
    }
}