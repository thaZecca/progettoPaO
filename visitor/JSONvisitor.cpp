#include "include/JSONvisitor.hpp"
#include "../model/include/contenutoMultimediale.hpp"
#include "../model/include/supportoMultimediale.hpp"
#include "../model/include/digitale.hpp"
#include "../model/include/fileAudio.hpp"
#include "../model/include/videoD.hpp"
#include "../model/include/fileVideo.hpp"
#include "../model/include/cd.hpp"
#include "../model/include/dvd.hpp"

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

/*toJsonSM - trasforma le tracce del supporto multimediale in Json
@param sm supporto multimediale da trasformare in json*/
void JSONvisitor::toJsonSM(const supportoMultimediale* sm){
    vector<contenutoMultimediale*> contenuti= sm -> getTracce();
    audioD* p = dynamic_cast<audioD*>(*contenuti.begin()); //so che il tipo dei supportiMultimediali è coerente (o solo file audio, o solo file video)
    QJsonArray root;
    for(auto it=contenuti.begin(); it!=contenuti.end(); it++){
        if(p) visit(static_cast<audioD*>(*it));
        else visit(static_cast<videoD*>(*it));
        root.append(jsonMedia);
    }
    jsonMedia = QJsonObject();
    jsonMedia["tracce"] = root;
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
    jsonMedia = QJsonObject();
    toJsonSM(c);
    jsonMedia["tipo"] = "CD";
    jsonMedia["diametro"] = c -> getDiametro();
}

/*visit - trasforma l'oggetto videoD in Json
@param video videoD da trasformare in json*/
void JSONvisitor::visit(videoD* video){
    jsonMedia = QJsonObject();
    toJsonCM(video);
    toJsonDig(video);
    jsonMedia["fps"] = static_cast<int>(video -> getFPS());
    jsonMedia["progressivo"] = (video -> isProgressivo()?"true":"false");
    jsonMedia["risoluzione"] = video -> getRisoluzione();
    jsonMedia["tipo"] = "videoD";
}

/*visit - trasforma l'oggetto fileVideo in Json
@param fv fileVideo da trasformare in json*/
void JSONvisitor::visit(fileVideo* fv){
    visit(static_cast<videoD*>(fv));
    jsonMedia["estensione"] = fv -> getEstensione();
    jsonMedia["tipo"] = "fileVideo";
}

/*visit - trasforma l'oggetto dvd in Json
@param d dvd da trasformare in json*/
void JSONvisitor::visit(dvd* d){
    jsonMedia = QJsonObject();
    toJsonSM(d);
    jsonMedia["tipo"] = "DVD";
    jsonMedia["diametro"] = d -> getDiametro();
} 

/*getJson
@return l'oggetto Json del singolo media*/
QJsonObject& JSONvisitor::getJson(){
    return jsonMedia;
}