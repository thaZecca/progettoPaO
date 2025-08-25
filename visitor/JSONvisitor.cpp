#include "include/JSONvisitor.hpp"
#include "../model/include/contenutoMultimediale.hpp"
#include "../model/include/digitale.hpp"
#include "../model/include/fileAudio.hpp"
#include "../model/include/cd.hpp"

/*toJsonCM - Trasforma il sottooggetto contenutoMultimediale in Json
@param cm contenuto multimediale da trasformare in json
*/
void JSONvisitor::toJsonCM(const contenutoMultimediale* cm){
    jsonMedia["titolo"] = cm -> getTitolo();
    jsonMedia["casaProdutrice"] = cm -> getCasaProduttrice();
    vector<QString> autori = cm -> getAutori();
    int num = 0;
    for(auto a = autori.begin(); a != autori.end(); a++){
        jsonMedia[QString("autore%1").arg(num)] = *a; num++;
    }
    jsonMedia["pubblicazione"] = static_cast<int>(cm -> getAnnoDiPubblicazione());
    jsonMedia["durata"] = static_cast<int>(cm -> getDurataSecondi());
    jsonMedia["picPath"] = (cm -> getPicPath());
}

/*toJsonDig - trasforma il sottooggetto digitale in Json
@param dig digitale da trasformare in json*/
void JSONvisitor::toJsonDig(const digitale* dig){
    jsonMedia["peso"] = (dig -> getPeso());
}

/*visit - trasforma l'oggetto audioD in json
@param audio audioD da trasformare in json*/
void JSONvisitor::visit(audioD* audio){
    jsonMedia = QJsonObject();
    jsonMedia["tipo"] = "audioD";
    toJsonCM(audio);
    toJsonDig(audio);
    jsonMedia["frequenza"] = static_cast<int>(audio -> getFrequenzaCampionamento()); //
    jsonMedia["stereo"] = (audio -> isStereo()?"true":"false");
    jsonMedia["canali"] = static_cast<int>(audio -> getNumeroCanali()); //
}

/*visit - trasforma l'oggetto fileAudio in json
@param fa fileAudio da trasformare in json*/
void JSONvisitor::visit(fileAudio* fa){
    visit(static_cast<audioD*>(fa));
    jsonMedia["tipo"] = "fileAudio";
    jsonMedia["lossy"] = (fa -> isLossy()?"true":"false");
    jsonMedia["estensione"] = fa -> getEstensione();
}

/*visit - trasforma l'oggetto cd in Json
@param c cd da trasformare in Json*/
void JSONvisitor::visit(cd* c){
    //creo il json per ogni traccia audio
    vector<audioD> a = c -> getTracceAudio();
    for(auto i = a.begin(); i != a.end(); i++){
        audioD* ptr = &(*i);
        visit(ptr); //viene salvato il json in jsonMedia
        QJsonObject appoggio = jsonMedia; //creo una copia dell'oggetto json
        jsonMore.push_back(appoggio); //inserisco la copia nell'array
    }
    jsonMedia = QJsonObject(); //riinizializzo l'oggetto json
    jsonMedia["tipo"] = "cd"; //lo sistemo perchè contenga le intestazioni per il cd
}

void JSONvisitor::visit(videoD* video){}

void JSONvisitor::visit(fileVideo* fv){}

void JSONvisitor::visit(dvd* d){} 

/*getJson
@return l'oggetto Json del singolo media*/
QJsonObject& JSONvisitor::getJson(){
    return jsonMedia;
}

/*getJsonMore
@retrun il vettore di oggetti Json dei media compositi (contenuti di cd e dvd)*/
vector<QJsonObject>& JSONvisitor::getJsonMore(){
    return jsonMore;
}