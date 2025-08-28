#include "./include/fileAudio.hpp"

/*Costruttore parametrico completo di fileAudio
@param t titolo del contenuto multimediale
@param cP casa produttrice
@param a vettore degli autori
@param aDPubb anno di pubblicazione
@param d durata espressa in secondi
@param pP percorso dell'immagine
@param p peso del contenuto multimediale digitale espresso in MB
@param fC frequenza dei campionamento audio espressa in Hz
@param s true se il fileAudio è stereo, false altrimenti
@param nC numero canali dell'audioD
@param l true se il fileAudio è lossy, false altrimenti
@param e estensione del fileAudio*/
fileAudio::fileAudio(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, float p, unsigned int fC, bool s, unsigned int nC, bool l, QString e): audioD(t,cP,a,aDPubb,d,pP,p,fC,s,nC), lossy(l), estensione(e) {}

/*isLossy
@return true se *this è lossy, false altrimenti*/
bool fileAudio::isLossy() const{
    return lossy;
}

/*getEstensione
@return estensione del fileAudio*/
QString fileAudio::getEstensione() const{
    return estensione;
}

/*setLossy
l true se il fileAudio è lossy, false altrimenti*/
void fileAudio::setLossy(bool l){
    lossy = l;
}

/*setEstensione
@param e estensione da dare al fileAudio*/
void fileAudio::setEstensione(QString e){
    estensione = e;
}

/*accept - design pattern per accedere all'oggetto
@param v visitor*/
void fileAudio::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*operator<< esterno
@param os stream di output
@param fA fileAudio da stampare*/
ostream& operator<<(ostream& os, const fileAudio& fA){
    operator<<(os, static_cast<const audioD&>(fA));
    os << "\nFILE AUDIO!!" << "\n" << "Estensione: " << fA.estensione.toStdString() << "\n" << (fA.lossy?"Lossy":"Lossless");
    return os;
}