#include "./include/supportoMultimediale.hpp"

/*Costruttore parametrico completo
@param s scaffale dove si trova il supporto multimediale*/
supportoMultimediale::supportoMultimediale(const QString& s): scaffale(s) {} 

/*isInPrestito
@return true se in prestito, false altrimenti*/
bool supportoMultimediale::isInPrestito() const{
    return inPrestito;
}

/*setInprestito
@param p valore da impostare al prestito, true se in prestito, false altrimenti*/
void supportoMultimediale::setInPrestito(bool p){
    inPrestito = p;
}

/*getDataPrestito
@return data del prestito*/
QDate supportoMultimediale::getDataPrestito() const{
    return dataPrestito;
}

/*setDataPrestito
@param d data da impostare al prestito*/
void supportoMultimediale::setDataPrestito(const QDate& data){
    dataPrestito = data;
}

/*getDurataPrestito
@return la durata del prestito*/
int supportoMultimediale::getDurataPrestito() const{
    return durataPrestito;
}

/*setDurataPrestito
@param d durata del prestito*/
void supportoMultimediale::setDurataPrestito(int d){
    durataPrestito = d;
}

/*getNomePrestito
@return nome della persona che ha preso in prestito il supporto*/
QString supportoMultimediale::getNomePrestito() const{
    return nomePrestito;
}

/*setNomePrestito
@param nP nome della persona che ha preso in prestito il supporto*/
void supportoMultimediale::setNomePrestito(const QString& nP){
    nomePrestito = nP;
}

/*getScaffale
@return il codice dello scaffale del supportoMultimediale*/
QString supportoMultimediale::getScaffale() const{
    return scaffale;
}

/*setScaffale
@param s codice dello scaffale da impostare al supporto*/
void supportoMultimediale::setScaffale(const QString& s){
    scaffale = s;
}
