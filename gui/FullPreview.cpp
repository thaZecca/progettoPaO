#include "include/FullPreview.hpp"

/*Costruttore parametrico di FullPreview
@param ip indexposition dell'oggetto da mostrare
@param q ultima query effettuata
@param parent QWidget parent*/
FullPreview::FullPreview(int ip, query* q, QWidget* parent): QWidget(parent), i(ip){
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
    connect(modifica, &QPushButton::clicked, this, &FullPreview::modifica_bounce);
}

/*prepare - prepara la fullpreview
@param ip index position dell'oggetto da mostrare
@param q ultima query eseguita*/
void FullPreview::prepare(int ip, query* q){
    vector<contenutoMultimediale*> c = biblioteca::instance().getContenuti();
    vector<supportoMultimediale*> s = biblioteca::instance().getSupporti();
    if(q) q -> filter(c,s);
    contenutoMultimediale* objC = biblioteca::cSearch(ip,c);
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

/*modifica_bounce - slot che effettua il bounce del segnale di modifica e integra l'index position*/
void FullPreview::modifica_bounce(){
    emit(modifica_event(i));
}