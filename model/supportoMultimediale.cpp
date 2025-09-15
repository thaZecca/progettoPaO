#include "./include/supportoMultimediale.hpp"

/*Costruttore parametrico completo
@param s scaffale dove si trova il supporto multimediale*/
supportoMultimediale::supportoMultimediale(const QString& s, const QString& t): titolo(t), scaffale(s) {} 

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
    os << s.titolo.toStdString() << " - " << s.scaffale.toStdString();
    return os;
}
