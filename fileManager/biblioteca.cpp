#include "./include/biblioteca.hpp"

/*Costruttore parametrico
@param path percorso per il fileManager*/
biblioteca::biblioteca(QString path): fM(path) {}

biblioteca::~biblioteca(){
    fM.save(contenuti, supporti);
}

/*projectPath - ritorna il percorso della cartella del progetto tramite direttive cross-platform*/
QDir biblioteca::projectPath() const{
    QDir dir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_MAC) //direttiva per sistema operativo Apple macOS
        dir.cdUp(); dir.cdUp(); dir.cdUp(); 
    #else //direttiva per sistemi Linux e Microsoft Windows
        dir.cdUp();
    #endif
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
    b.getFileManager().load(b.getContenuti(), b.getSupporti());
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

