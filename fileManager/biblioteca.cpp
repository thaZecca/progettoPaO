#include "./include/biblioteca.hpp"

/*Costruttore parametrico
@param path percorso per il fileManager*/
biblioteca::biblioteca(QString path): fM(path){
    load();
}

biblioteca::~biblioteca(){
    save();
}

/*projectPath - ritorna il percorso della cartella del progetto tramite direttive cross-platform*/
QDir biblioteca::projectPath(){
    QDir dir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_MAC) //direttiva per sistema operativo Apple macOS
        dir.cdUp(); dir.cdUp(); dir.cdUp(); 
    #else //direttiva per sistemi Linux e Microsoft Windows
        dir.cdUp();
    #endif
    return dir;
}

/*getFileManager
@return il file manager della biblioteca*/
fileManager& biblioteca::getFileManager(){
    return fM;
}

/*instance
@return il singleton di biblioteca*/
biblioteca& biblioteca::instance(){
    QString path = biblioteca::projectPath().filePath("storage.json");
    static biblioteca b(path);
    return b;
}

/*getContenuti
@return il riferimento ai contenuti multimediali*/
vector<contenutoMultimediale*>& biblioteca::getContenuti(){
    return contenuti;
}

/*getSupporti
@return il riferimento ai supporti multimediali*/
vector<supportoMultimediale*>& biblioteca::getSupporti(){
    return supporti;
}

/*presta - presta il contenuto multimediale c
@param c contenutoMultimediale da prestare
@param nome nome della persona che prende in presito il contenuto
@param data data in cui il contenuto viene preso in prestito
@param giorni durata in giorni del prestito*/
void biblioteca::presta(contenutoMultimediale* c, QString nome, QDate data, int giorni){
    c -> setInPrestito(true);
    c -> setNomePrestito(nome);
    c -> setDataPrestito(data);
    c -> setDurataPrestito(giorni);
}

/*presta - presta il supporto multimediale s
@param s supportoMultimediale da prestare
@param nome nome della persona che prende in presito il supporto
@param data data in cui il supporto viene preso in prestito
@param giorni durata in giorni del prestito*/
void biblioteca::presta(supportoMultimediale* s, QString nome, QDate data, int giorni){
    s -> setInPrestito(true);
    s -> setNomePrestito(nome);
    s -> setDataPrestito(data);
    s -> setDurataPrestito(giorni);
}

/*rientra - rientro del contenuto multimediale preso in prestito
@param c contenuto da rientrare*/
void biblioteca::rientra(contenutoMultimediale* c){
    c -> setInPrestito(false);
    c -> setNomePrestito("");
    c -> setDataPrestito(QDate());
    c -> setDurataPrestito(0);
}

/*rientra - rientro del supporto multimediale preso in prestito
@param s supporto da rientrare*/
void biblioteca::rientra(supportoMultimediale* s){
    s -> setInPrestito(false);
    s -> setNomePrestito("");
    s -> setDataPrestito(QDate());
    s -> setDurataPrestito(0);
}

/*save - salva nel file di storage lo stato dei contenuti e dei supporti*/
void biblioteca::save(){
    fM.save(contenuti, supporti);
}

/*load - carica dal file di storage il contenuto dei contenuti e dei supporti*/
void biblioteca::load(){
    contenuti.erase(contenuti.begin(), contenuti.end()); //svuoto i contenuti
    supporti.erase(supporti.begin(), supporti.end()); //svuoto i supporti
    fM.load(contenuti, supporti);
}

/*cSearch - ricerca tra i contenutiMultimediali alla posizione specificata
@param pos posizione in cui cercare
@param c vettore dei contenuti multimeidali
@param s vettore dei supporti multimediali
@return il contenutoMultimediale cercato se esiste, nullptr altrimenti*/
contenutoMultimediale* biblioteca::cSearch(int pos, vector<contenutoMultimediale*>& c, vector<supportoMultimediale*>& s){
    contenutoMultimediale* ret = nullptr;
    if(pos>=0 && pos<c.size()){
        ret = c[pos];
    }
    return ret;
}

/*cSearch - ricerca tra i supportiMultimediali alla posizione specificata
@param pos posizione in cui cercare
@param c vettore dei contenuti multimeidali
@param s vettore dei supporti multimediali
@return il supportoMultimediale cercato se esiste, nullptr altrimenti*/
supportoMultimediale* biblioteca::sSerach(int pos, vector<contenutoMultimediale*>& c, vector<supportoMultimediale*>& s){
    supportoMultimediale* ret = nullptr;
    pos = pos - (c.size() - 1);
    if(pos>=0 && pos<s.size()){
        ret = s[pos];
    }
    return ret;
}

