#include "./include/fileManager.hpp"

/*Costruttore parametrico completo
@param path percorso per istanziare l'oggetto file*/
fileManager::fileManager(QString path): file(path) {} 

/*save - salva i contenuti multimediali e i supporti multimediali sul file locale json
@param cInPossesso vettore di puntatori ai contenuti multimediali in possesso
@param cInPrestito vettore di puntatori ai contenuti multimediali in prestito
@param sInPossesso vettore di puntatori ai supporti multimediali in possesso
@param sInPrestito vettore di puntatori ai supporto multimediali in prestito*/
void fileManager::save(const vector<contenutoMultimediale*>& contenuti, const vector<supportoMultimediale*>& supporti){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cerr << "Errore nell'apertura del file per la scrittura!" << std::endl;
        return;
    }
    
    QJsonArray cont;
    JSONvisitor visitor;
    for(auto it=contenuti.begin(); it!=contenuti.end(); it++){
        (*it) -> accept(visitor);
        cont.append(visitor.getJson());
    }
    QJsonArray supp;
    for(auto it=supporti.begin(); it!=supporti.end(); it++){
        (*it) -> accept(visitor);
        supp.append(visitor.getJson());
    }

    QJsonObject root;
    root["contenuti"] = cont;
    root["supporti"] = supp;
    QJsonDocument doc(root);
    file.write(doc.toJson());
    
    file.close();
}

/*load - caricamento dei contenuti multimediali e dei supporti multimediali da file locale json
@param contenuti vettore di puntatori ai contenuti multimediali
@param supporti vettore di puntatori ai supporti multimediali*/
void fileManager::load(vector<contenutoMultimediale*>& contenuti, vector<supportoMultimediale*>& supporti){
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cerr << "Errore nell'apertura del file per la lettura!" << std::endl;
        return;
    }

    QByteArray dati = file.readAll(); //leggo tutto
    file.close(); //chiudo il file perchè non mi serve più

    QJsonDocument doc(QJsonDocument::fromJson(dati));

    if(!doc.isObject()){
        qWarning("Errore nella composizione del file JSON");
        return;
    }
    QJsonObject root = doc.object();

    QJsonArray cont = root["contenuti"].toArray();
    for(auto it=cont.begin(); it!=cont.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="audioD"){
            audioD* ptr = fileManager::getAudioD(obj);
            if(ptr) contenuti.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileAudio"){
            fileAudio* ptr = fileManager::getFileAudio(obj);
            if(ptr) contenuti.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="videoD"){
            videoD* ptr = fileManager::getVideoD(obj);
            if(ptr) contenuti.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileVideo"){
            fileVideo* ptr = fileManager::getFileVideo(obj);
            if(ptr) contenuti.push_back(ptr);
        }
    }

    QJsonArray supp = root["supporti"].toArray();
    for(auto it=supp.begin(); it!=supp.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="CD"){
            cd* ptr = fileManager::getCD(obj);
            if(ptr) supporti.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="DVD"){
            dvd* ptr = fileManager::getDVD(obj);
            if(ptr) supporti.push_back(ptr);
        }
    }

}

/*getAudioD - costruisce l'oggetto audioD a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto audioD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
audioD* fileManager::getAudioD(const QJsonObject& o){
    audioD* ret = nullptr;
    if(o["titolo"].isString() && o["stereo"].isString() && 
            o["picPath"].isString() && o["casaProduttrice"].isString() && o["pubblicazione"].isDouble() && 
            o["peso"].isDouble() && o["frequenza"].isDouble() && o["durata"].isDouble() && o["canali"].isDouble() && o["scaffale"].isString()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new audioD(o["titolo"].toString(), o["casaProduttrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["frequenza"].toInt(), o["stereo"].toString().toStdString() == "true", o["canali"].toInt());
                ret -> setScaffale(o["scaffale"].toString());
            }
    return ret;
}

/*getFileAudio - costruisce l'oggetto fileAudio a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto fileAudio
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
fileAudio* fileManager::getFileAudio(const QJsonObject& o){
    fileAudio* ret = nullptr;
    if(o["titolo"].isString() && o["stereo"].isString() && 
            o["picPath"].isString() && o["casaProduttrice"].isString() && o["pubblicazione"].isDouble() && 
            o["lossy"].isString() && o["estensione"].isString() && o["peso"].isDouble() && 
            o["frequenza"].isDouble() && o["durata"].isDouble() && o["canali"].isDouble() && o["scaffale"].isString()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new fileAudio(o["titolo"].toString(), o["casaProduttrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["frequenza"].toInt(), o["stereo"].toString().toStdString() == "true", o["canali"].toInt(), o["lossy"].toString().toStdString() == "true", o["estensione"].toString());
                ret -> setScaffale(o["scaffale"].toString());
            }
    return ret;
}

/*getVideoD - costruisce l'oggetto videoD a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto videoD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
videoD* fileManager::getVideoD(const QJsonObject& o){
    videoD* ret = nullptr;
    if(o["titolo"].isString() && 
            o["picPath"].isString() && o["casaProduttrice"].isString() && o["pubblicazione"].isDouble() && 
            o["progressivo"].isString() && o["risoluzione"].isString() && o["peso"].isDouble() && 
            o["durata"].isDouble() && o["fps"].isDouble() && o["scaffale"].isString()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new videoD(o["titolo"].toString(), o["casaProduttrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["fps"].toInt(), o["progressivo"].toString().toStdString() == "true", o["risoluzione"].toString());
                ret -> setScaffale(o["scaffale"].toString());
            }
        return ret;
}

/*getFileVideo - costruisce l'oggetto fileVideo a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto fileVideo
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
fileVideo* fileManager::getFileVideo(const QJsonObject& o){
    fileVideo* ret = nullptr;
    if(o["titolo"].isString() && 
            o["picPath"].isString() && o["casaProduttrice"].isString() && o["pubblicazione"].isDouble() && 
            o["progressivo"].isString() && o["risoluzione"].isString() && o["peso"].isDouble() && 
            o["durata"].isDouble() && o["fps"].isDouble() && o["estensione"].isString() && o["scaffale"].isString()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new fileVideo(o["titolo"].toString(), o["casaProduttrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["fps"].toInt(), o["progressivo"].toString().toStdString() == "true", o["risoluzione"].toString(), o["estensione"].toString());
                ret -> setScaffale(o["scaffale"].toString());
            }
        return ret;
}

/*getCD - costruisce l'oggetto CD a partire dalla sua serializzazione in Json
@param o serializzazione json dell'oggetto CD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
cd* fileManager::getCD(const QJsonObject& o){
    cd* ret = nullptr;
    if(o["diametro"].isDouble() && o["scaffale"].isString() && o["titolo"].isString()){
        vector<audioD*> tracceAudio;
        QJsonArray tracce = o["tracce"].toArray();
        for(auto it = tracce.begin(); it!=tracce.end(); it++){
            if((*it).isObject()){
                audioD* ptr = fileManager::getAudioD((*it).toObject());
                if(ptr) tracceAudio.push_back(ptr);
            }
        }
        ret = new cd(tracceAudio, o["diametro"].toDouble(), o["scaffale"].toString(), o["titolo"].toString());
        ret -> setScaffale(o["scaffale"].toString());
    }
    return ret;
}

/*getDVD - costruisce l'oggetto DVD a partire dalla sua serializzazione in Json
@param o serializzazione json dell'oggetto DVD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
dvd* fileManager::getDVD(const QJsonObject& o){
    dvd* ret = nullptr;
    if(o["diametro"].isDouble() && o["scaffale"].isString() && o["titolo"].isString()){
        vector<videoD*> tracceVideo;
        QJsonArray tracce = o["tracce"].toArray();
        for(auto it = tracce.begin(); it!=tracce.end(); it++){
            if((*it).isObject()){
                videoD* ptr = fileManager::getVideoD((*it).toObject());
                if(ptr) tracceVideo.push_back(ptr);
            }
        }
        ret = new dvd(tracceVideo, o["diametro"].toDouble(), o["scaffale"].toString(), o["titolo"].toString());
        ret -> setScaffale(o["scaffale"].toString());
    }
    return ret;
}