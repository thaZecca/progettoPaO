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
        jsonMedia["autore"+std::to_string(num)] = *a;
    }
    jsonMedia["pubblicazione"] = std::to_string(cm -> getAnnoDiPubblicazione());
    jsonMedia["durata"] = std::to_string(cm -> getDurataSecondi());
    jsonMedia["picPath"] = std::to_string(cm -> getPicPath());
}

/*toJsonDig - trasforma il sottooggetto digitale in Json
@param dig digitale da trasformare in json*/
void JSONvisitor::toJsonDig(const digitale* dig){
    jsonMedia["peso"] = std::to_string(dig -> getPeso());
}

/*visitAudioD - trasforma l'oggetto audioD in json
@param audio audioD da trasformare in json*/
void JSONvisitor::visitAudioD(audioD* audio) override{
    jsonMedia = QJsonObject();
    jsonMedia["tipo"] = "audioD";
    toJsonCM(audio);
    toJsonDig(audio);
    jsonMedia["frequenza"] = std::to_string(audio -> getFrequenzaCampionamento());
    jsonMedia["stereo"] = (audio -> isStereo()?"true":"false");
    jsonMedia["canali"] = std::to_string(audio -> getNumeroCanali());
}

/*visitFileAudio - trasforma l'oggetto fileAudio in json
@param fa fileAudio da trasformare in json*/
void JSONvisitor::visitFileAudio(fileAudio* fa) override{
    visitAudioD(fa);
    jsonMedia["tipo"] = "fileAudio";
    jsonMedia["lossy"] = (fa -> isLossy()?"true":"false");
    jsonMedia["estensione"] = fa -> getEstensione();
}

void JSONvisitor::visitCD(cd* c) override{
    //creo il json per ogni traccia audio
    vector<audioD> a = c -> getTracceAudio();
    for(auto i = a -> begin(); i != a -> end(); i++){
        visitAudioD(*i); //viene salvato il json in jsonMedia
        QJsonObject appoggio = jsonMedia; //creo una copia dell'oggetto json
        jsonMore.push_back(appoggio); //inserisco la copia nell'array
    }
    jsonMedia = QJsonObject(); //riinizializzo l'oggetto json
    jsonMedia["tipo"] = "cd"; //lo sistemo perchè contenga le intestazioni per il cd
    jsonMedia["tracce"] = std::to_string(c -> getTracceAudio() -> size());
}

void JSONvisitor::visitVideoD(videoD* video) override{}

void JSONvisitor::visitFileVideo(fileVideo* fv) override{}

void JSONvisitor::visitDVD(dvd* d) override{} 