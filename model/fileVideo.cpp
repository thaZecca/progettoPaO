#include "./include/fileVideo.hpp"

/*Costruttore parametrico completo di classe fileVideo
@param t titolo del fileVideo
@param cP casa produttrice
@param a vettore degli autori
@param aDPubb anno di pubblicazione
@param d durata espressa in secondi
@param pP percorso dell'immagine
@param p peso del fileVideo digitale espresso in MB
@param f fps del fileVideo
@param isP true se il fileVideo è progressivo, false altrimenti
@param r risoluzione del fileVideo
@param e estensione del fileVideo
*/
fileVideo::fileVideo(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, float p, unsigned int f, bool isP, QString r, QString e): videoD(t,cP,a,aDPubb,d,pP,p,f,isP,r), estensione(e) {}

/*getEstensione
@return l'estensione del fileVideo*/
QString fileVideo::getEstensione() const{
    return estensione;
}

/*setEstensione
@param e estensione del fileVideo*/
void fileVideo::setEstensione(QString e){
    estensione = e;
}

/*accept - design pattern per accedere all'oggetto
@param v visitor*/
void fileVideo::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*operator<< esterno
@param os stream di output
@param fV fileVideo da stampare*/
ostream& operator<<(ostream& os, const fileVideo& fV){
    operator<<(os, static_cast<const videoD&>(fV));
    os << "\n" << "Estensione: " << fV.estensione.toStdString();
    return os;
}