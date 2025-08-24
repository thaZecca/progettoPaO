#include "./include/digitale.hpp"

/*Costruttore parametrico completo di classe digitale
@param t titolo del contenuto multimediale
@param cP casa produttrice
@param a vettore degli autori
@param aDProd anno di produzione
@param aDPubb anno di pubblicazione
@param d durata espressa in secondi
@param pP percorso dell'immagine
@param p peso del contenuto multimediale digitale in MB*/
digitale::digitale(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, float p): contenutoMultimediale(t, cP, a, aDPubb, d, pP), peso(p) {}

/*getPeso
@return il peso del contenuto multimediale digitale espresso in MB*/
float digitale::getPeso() const{
    return peso;
}

/*setPeso
@param p il peso da impostare*/
void digitale::setPeso(float p){
    peso = p;
}

ostream& operator<<(ostream& os, const digitale& d){
    operator<<(os,static_cast<const contenutoMultimediale&>(d));
    os << "\n" << "Peso: " << std::to_string(d.peso) << "MB";
    return os;
}