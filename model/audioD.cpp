#include "./include/audioD.hpp"

/*Costruttore parametrico completo di classe audioD
@param t titolo del contenuto multimediale
@param cP casa produttrice
@param a vettore degli autori
@param aDPubb anno di pubblicazione
@param d durata espressa in secondi
@param pP percorso dell'immagine
@param sc scaffale dell'audioD
@param p peso del contenuto multimediale digitale espresso in MB
@param fC frequenza dei campionamento audio espressa in Hz
@param s true se l'audioD è stereo, false altrimenti
@param nC numero canali dell'audioD*/
audioD::audioD(QString t, QString cP, vector<QString> a, unsigned int aDPubb, unsigned int d, QString pP, QString sc, float p, unsigned int fC, bool s, unsigned int nC): digitale(t,cP,a,aDPubb,d,pP,sc,p), frequenzaCampionamento(fC), stereo(s), numeroCanali(nC) {}

/*getFrequenzaCampionamento
@return la frequenza di campionamento espressa in kHz*/
unsigned int audioD::getFrequenzaCampionamento() const{
    return frequenzaCampionamento;
}

/*isStereo
@return true se l'audioD è stereo, false altrimenti*/
bool audioD::isStereo() const{
    return stereo;
}

/*getNumeroCanali
@return il numero di canali audio dell'audioD*/
unsigned int audioD::getNumeroCanali() const{
    return numeroCanali;
}

/*setFrequenzaCampionamento
@param fC nuova frequenza di campionamento dell'audioD*/
void audioD::setFrequenzaCampionamento(unsigned int fC){
    frequenzaCampionamento = fC;
}

/*setIsStereo
@param isS true se il contenuto è stereo, false altrimenti*/
void audioD::setStereo(bool s){
    stereo = s;
}

/*setNumeroCanali
@param nC nuovo numero di canali da impostare*/
void audioD::setNumeroCanali(unsigned int nC){
    numeroCanali = nC;
}

/*accept -  design pattern per accedere all'ggetto
@param v visitor*/
void audioD::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*operator<< esterno
@param os stream di output
@param aD audioD da stampare*/
ostream& operator<<(ostream& os, const audioD& aD){
    operator<<(os,static_cast<const digitale&>(aD));
    os << "\n" << "Freq. camp. " << std::to_string(aD.frequenzaCampionamento) << ", " << (aD.stereo?"stereo":"mono") << "\n" << "Numero canali: " << std::to_string(aD.numeroCanali);
    return os;
}