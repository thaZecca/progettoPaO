#include "./include/contenutoMultimediale.hpp"
#include <string>

/*Costruttore parametrico completo di classe contenutoMultimediale
@param t titolo del contenuto multimediale
@param cP casa produttrice
@param a vettore degli autori
@param aDPubb anno di pubblicazione
@param d durata espress in secondi
@param pP percorso dell'immagine
@param s scaffale del contenutoMultimendiale*/
contenutoMultimediale::contenutoMultimediale(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, QString s): titolo(t), casaProduttrice(cP), autori(a), annoDiPubblicazione(aDPubb), durataSecondi(d), picPath(pP), scaffale(s) {}

/*Distruttore per evitare undefined symbols*/
contenutoMultimediale::~contenutoMultimediale() {}

/*getTitolo
@return il titolo del contenuto multimediale*/
QString contenutoMultimediale::getTitolo() const{
    return titolo;
}

/*getCasaProduttrice
@return casa produttrice del contenuto*/
QString contenutoMultimediale::getCasaProduttrice() const{
    return casaProduttrice;
}

/*getAutori
@return la lista degli autori del contenuto*/
vector<QString> contenutoMultimediale::getAutori() const{
    return autori;
}

/*getAnnoDiPubblicazione
@return l'anno di pubblicazione del contenuto*/
unsigned int contenutoMultimediale::getAnnoDiPubblicazione() const{
    return annoDiPubblicazione;
}

/*getDurataSecondi
@return la durata del contenuto multimediale espresso in secondi*/
unsigned int contenutoMultimediale::getDurataSecondi() const{
    return durataSecondi;
}

/*getPicPath
@return il percorso dell'immagine del contenuto multimediale*/
QString contenutoMultimediale::getPicPath() const{
    return picPath;
}

/*setTitolo
@param t il nuovo titolo*/
void contenutoMultimediale::setTitolo(const QString& t){
    titolo=t;
}

/*setCasaProduttrice
@param cP la nuova casa produttrice*/
void contenutoMultimediale::setCasaProdutttrice(const QString& cP){
    casaProduttrice=cP;
}

/*setAutori
@param a nuova lista degli autori*/
void contenutoMultimediale::setAutori(const vector<QString>& a){
    autori=a;
}

/*setAutore
imposta un solo autore
@param p posizione dell'autore da modificare
@param a il nuovo autore*/
void contenutoMultimediale::setAutore(unsigned int p, const QString& a){
    autori.emplace(autori.begin()+p, a);
}

/*setAnnoDiPubblicazione
@param aDPubb anno di pubblicazione*/
void contenutoMultimediale::setAnnoDiPubblicazione(unsigned int aDPubb){
    annoDiPubblicazione=aDPubb;
}

/*setDurataSecondi
@prama d durata espressa in secondi*/
void contenutoMultimediale::setDurataSecondi(unsigned int d){
    durataSecondi=d;
}

/*setPicPath
@param p nuovo percorso dell'immagine*/
void contenutoMultimediale::setPicPath(const QString& pP){
    picPath=pP;
}

/*getScaffale
@return il codice dello scaffale del contenutoMultimediale*/
QString contenutoMultimediale::getScaffale() const{
    return scaffale;
}

/*setScaffale
@param s codice dello scaffale da impostare al contenuto*/
void contenutoMultimediale::setScaffale(const QString& s){
    scaffale = s;
}

/*operator<< esterno
@param os stream di output
@param c contenutoMultimediale da stampare
@return stream di output*/
ostream& operator<<(ostream& os, const contenutoMultimediale& c){
    os << c.titolo.toStdString() << " - " << c.casaProduttrice.toStdString() << " - " "Pubblicazione: " << std::to_string(c.annoDiPubblicazione) << "\n";
    os << "Autori: ";
    for(auto cit = c.autori.begin(); cit != c.autori.end(); cit++){
        os << (*cit).toStdString() << ", ";
    }
    unsigned int min = static_cast<unsigned int>(c.durataSecondi / 60);
    unsigned int sec = c.durataSecondi % 60;
    os << "\n" << "Durata: " << std::to_string(min) << " min " << std::to_string(sec) << " sec" << "\n" << "Pp: " << c.picPath.toStdString();
    return os;
}