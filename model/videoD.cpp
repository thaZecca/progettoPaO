#include "./include/videoD.hpp"

/*Costruttore parametrico completo di classe videoD
@param t titolo del contenuto multimediale
@param cP casa produttrice
@param a vettore degli autori
@param aDPubb anno di pubblicazione
@param d durata espressa in secondi
@param pP percorso dell'immagine
@param p peso del contenuto multimediale digitale espresso in MB
*/
videoD::videoD(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, float p, unsigned int f, bool isP, QString r): digitale(t,cP,a,aDPubb,d,pP,p), fps(f), progressivo(isP), risoluzione(r) {}

/*getFPS
@return gli FPS del videoD*/
unsigned int videoD::getFPS() const{
    return fps;
}

/*isProgressivo
@return true se videoD è progressivo, false altrimenti*/
bool videoD::isProgressivo() const{
    return progressivo;
}

/*getRisoluzione
@return la risoluzione di videoD*/
QString videoD::getRisoluzione() const{
    return risoluzione;
}

/*setFPS
@param f fps da impostare al videoD*/
void videoD::setFPS(unsigned int f){
    fps = f;
}

/*setProgressivo
@param isP true se il videoD è progressivo, false altrimenti*/
void videoD::setProgressivo(bool isP){
    progressivo = isP;
}

/*setRisoluzione
@param r risoluzione da impostare al videoD*/
void videoD::setRisoluzione(QString r){
    risoluzione = r;
}

void videoD::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*operator<< esterno
@param os stream di output
@param v videoD da stampare*/
ostream& operator<<(ostream& os, const videoD& v){
    operator<<(os, static_cast<const digitale&>(v));
    os << "\n" << v.fps << " fps - " << (v.progressivo?"Progressivo":"Non progressivo") << " - " << v.risoluzione.toStdString() << (v.progressivo?"p":"i");
    return os;
}