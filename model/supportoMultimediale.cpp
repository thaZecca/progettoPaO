#include "./include/supportoMultimediale.hpp"

/*Costruttore parametrico completo
@param s scaffale dove si trova il supporto multimediale*/
supportoMultimediale::supportoMultimediale(const QString& s, const QString t): scaffale(s), titolo(t) {} 

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

/*getTitolo
@return il titolo del supporto*/
QString supportoMultimediale::getTitolo() const{
    return titolo;
}

/*setTitolo
@param t titolo da impostare al supportoMultimediale*/
void supportoMultimediale::setTitolo(const QString& t){
    titolo = t;
}

/*operator<< esterno
@param os stream di output
@param s supporto multimediale da stampare
@return stream di output*/
ostream& operator<<(ostream& os, const supportoMultimediale& s){
    if(s.inPrestito){
        os << "\n" << "Supporto preso in prestito da " << s.nomePrestito.toStdString() << " il giorno " << s.dataPrestito.toString().toStdString() << ", restituzione prevista tra " << s.durataPrestito << " giorni.";   
    }else os << "Supporto non in prestito";
    return os;
}
