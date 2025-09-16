#include "./include/biblioteca.hpp"

//istanziazione della variabile del singleton pattern
biblioteca* biblioteca::_instance = nullptr;

/*Costruttore parametrico
@param path percorso per il fileManager*/
biblioteca::biblioteca(QString path): fM(path){
    load();
}

/*Distruttore - salva la biblioteca prima di distruggere l'oggetto*/
biblioteca::~biblioteca(){
    save();
}

/*init - inizializza il singleton
@param path percorso in cui si trova il file di storage della biblioteca*/
void biblioteca::init(const QString& path) {
    if (_instance == nullptr) {
         _instance = new biblioteca(path);
    }
}

/*projectPath - ritorna il percorso della cartella del progetto + direttive per Apple macOs*/
QDir biblioteca::projectPath(){
    QDir dir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_MAC) //direttiva per sistema operativo Apple macOS
        dir.cdUp(); dir.cdUp(); dir.cdUp();
    #endif
    return dir;
}

/*instance
@return il singleton di biblioteca*/
biblioteca& biblioteca::instance(){
    if(_instance == nullptr){
        throw QString("Nessuno storage selezionato!");
    }
    return *_instance;
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
@return il contenutoMultimediale cercato se esiste, nullptr altrimenti*/
contenutoMultimediale* biblioteca::cSearch(int pos, vector<contenutoMultimediale*>& c){
    contenutoMultimediale* ret = nullptr;
    if(pos>=0 && pos<static_cast<int>(c.size()) && !c.empty()){
        ret = c[pos];
    }
    return ret;
}

/*cSearch - ricerca tra i supportiMultimediali alla posizione specificata
@param pos posizione in cui cercare
@param c vettore dei contenuti multimeidali
@param s vettore dei supporti multimediali
@return il supportoMultimediale cercato se esiste, nullptr altrimenti*/
supportoMultimediale* biblioteca::sSearch(int pos, vector<contenutoMultimediale*>& c, vector<supportoMultimediale*>& s){
    supportoMultimediale* ret = nullptr;
    if(!c.empty()) pos -= (c.size());
    if(pos>=0 && pos<static_cast<int>(s.size()) && !s.empty()){
        ret = s[pos];
    }
    return ret;
}

/*add - aggiunge il contenutoMultimediale alla biblioteca
@param c contenutoMultimediale da aggiungere alla biblioteca, se nullptr continue*/
void biblioteca::add(contenutoMultimediale* c){
    if(c) biblioteca::instance().getContenuti().push_back(c);
}

/*add - aggiunge il supportoMultimediale alla biblioteca
@param s supportoMultimediale da aggiungere alla biblioteca, se nullptr continue*/
void biblioteca::add(supportoMultimediale* s){
    if(s) biblioteca::instance().getSupporti().push_back(s);
}

/*remove - rimuove l'oggetto corrispondente all'index position per la query specifica
@param ip index position dell'oggetto corrispondente
@param q query specifica dell'index position*/
void biblioteca::remove(int ip, query* q){
    vector<contenutoMultimediale*> cont = getContenuti();
    vector<supportoMultimediale*> supp = getSupporti();
    if(q) q -> filter(cont,supp);

    contenutoMultimediale* c = cSearch(ip, cont);
    supportoMultimediale* s = sSearch(ip, cont, supp);

    if(c){
        for(auto it = contenuti.begin(); it != contenuti.end();){
            if(*it == c) contenuti.erase(it);
            else it++;
        }
        delete c;
    }else{
        for(auto it = supporti.begin(); it != supporti.end();){
            if(*it == s) supporti.erase(it);
            else it++;
        }
        delete s;
    }
}
