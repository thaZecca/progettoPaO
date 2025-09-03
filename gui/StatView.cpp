#include "./include/StatView.hpp"

/*Costruttore parmetrico di StatView*/
StatView::StatView(QWidget* parent): QGroupBox("Statistiche",parent){
    //inizializzo le Qlabel altrimenti senza un "aggancio rimangono nullptr"
    tot = new QLabel(this);
    totC = new QLabel(this);
    totAD = new QLabel(this);
    totVD = new QLabel(this);
    totFA = new QLabel(this);
    totD = new QLabel(this);
    totFV = new QLabel(this);
    totPres = new QLabel(this);
    mainLayout = new QGridLayout(this);

    repaint();

    //QLabel che rimangono "statiche"
    QLabel* uno = new QLabel();
    uno -> setText("Totale contenuti e supporti:");
    mainLayout -> addWidget(uno,0,0);
    QLabel* due = new QLabel();
    due -> setText("CD:");
    mainLayout -> addWidget(due,1,0);
    QLabel* tre = new QLabel();
    tre -> setText("Audio digitale:");
    mainLayout -> addWidget(tre,2,0);
    QLabel* quattro = new QLabel();
    quattro -> setText("Video digitale:");
    mainLayout -> addWidget(quattro,3,0);
    QLabel* cinque = new QLabel();
    cinque -> setText("File audio:");
    mainLayout -> addWidget(cinque,4,0);
    QLabel* sei = new QLabel();
    sei -> setText("File video:");
    mainLayout -> addWidget(sei,5,0);
    QLabel* sette = new QLabel();
    sette -> setText("DVD:");
    mainLayout -> addWidget(sette,6,0);
    QLabel* otto = new QLabel();
    otto -> setText("In prestito:");
    mainLayout -> addWidget(otto,7,0);
}

/*repaint - "ripittura" l'interfaccia*/
void StatView::repaint(){
    prepare();
    mainLayout -> addWidget(tot,0,1);
    mainLayout -> addWidget(totC,1,1);
    mainLayout -> addWidget(totAD,2,1);
    mainLayout -> addWidget(totVD,3,1);
    mainLayout -> addWidget(totFA,4,1);
    mainLayout -> addWidget(totFV,5,1);
    mainLayout -> addWidget(totD,6,1);
    mainLayout -> addWidget(totPres,7,1);
}

/*prepare - prepare le statistiche da mostrare nella view*/
void StatView::prepare(){
    int total, fA, fV, aD, vD, c, d, prestito;
    total = fA = fV = aD = vD = c = d = prestito = 0;
    biblioteca& b = biblioteca::instance();
    total = b.getContenuti().size() + b.getSupporti().size();
    for(auto& c : b.getContenuti()){
        if(dynamic_cast<fileAudio*>(c)) fA++;
        else if(dynamic_cast<fileVideo*>(c)) fV++;
        else if(dynamic_cast<audioD*>(c)) aD++;
        else if(dynamic_cast<videoD*>(c)) vD++;

        if(c->isInPrestito()) prestito++;
    }
    for(auto& s : b.getSupporti()){
        if(dynamic_cast<cd*>(s)) c++;
        else if(dynamic_cast<dvd*>(s)) d++;

        if(s->isInPrestito()) prestito++;
    }

    tot -> setText(QString::number(total));
    totC -> setText(QString::number(c));
    totAD -> setText(QString::number(aD));
    totD -> setText(QString::number(d));
    totFA -> setText(QString::number(fA));
    totFV -> setText(QString::number(fV));
    totVD -> setText(QString::number(vD));
    totPres -> setText(QString::number(prestito));
}

