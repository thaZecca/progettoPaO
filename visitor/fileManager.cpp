#include "./include/fileManager.hpp"

fileManager::fileManager(QString path): file(path) {} 

void fileManager::save(const vector<contenutoMultimediale*>& cInPossesso, const vector<contenutoMultimediale*>& cInPrestito, const vector<supportoMultimediale*>& sInPossesso, const vector<supportoMultimediale*>& sInPrestito){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cerr << "Errore nell'apertura del file per la scrittura!" << std::endl;
        return;
    }
    
    QJsonArray cInPoss;
    JSONvisitor visitor;
    for(auto it=cInPossesso.begin(); it!=cInPossesso.end(); it++){
        (*it) -> accept(visitor);
        cInPoss.append(visitor.getJson());
    }
    QJsonArray cInPres;
    for(auto it=cInPrestito.begin(); it!=cInPrestito.end(); it++){
        (*it) -> accept(visitor);
        cInPres.append(visitor.getJson());
    }
    QJsonArray sInPoss;
    for(auto it=sInPossesso.begin(); it!=sInPossesso.end(); it++){
        (*it) -> accept(visitor);
        sInPoss.append(visitor.getJson());
    }
    QJsonArray sInPres;
    for(auto it=sInPrestito.begin(); it!=sInPrestito.end(); it++){
        (*it) -> accept(visitor);
        sInPres.append(visitor.getJson());
    }

    QJsonObject root;
    root["cInPossesso"] = cInPoss;
    root["cInPrestito"] = cInPres;
    root["sInPossesso"] = sInPoss;
    root["sInPrestito"] = sInPres;
    QJsonDocument doc(root);
    file.write(doc.toJson());
    
    std::cout << doc.isEmpty() << std::endl;
    file.close();
    std::cout << doc.toJson().toStdString() << std::endl;
}

void fileManager::load(vector<contenutoMultimediale*>& cInPossesso, vector<contenutoMultimediale*>& cInPrestito, vector<supportoMultimediale*>& sInPossesso, vector<supportoMultimediale*>& sInPrestito){
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

    QJsonArray cInPoss = root["cInPossesso"].toArray();
    for(auto it=cInPoss.begin(); it!=cInPoss.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="audioD"){
            audioD* ptr = fileManager::getAudioD(obj);
            if(ptr) cInPossesso.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileAudio"){
            fileAudio* ptr = fileManager::getFileAudio(obj);
            if(ptr) cInPossesso.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="videoD"){
            videoD* ptr = fileManager::getVideoD(obj);
            if(ptr) cInPossesso.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileVideo"){
            fileVideo* ptr = fileManager::getFileVideo(obj);
            if(ptr) cInPossesso.push_back(ptr);
        }
    }

    QJsonArray cInPres = root["cInPrestito"].toArray();
    for(auto it=cInPres.begin(); it!=cInPres.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="audioD"){
            audioD* ptr = fileManager::getAudioD(obj);
            if(ptr) cInPrestito.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileAudio"){
            fileAudio* ptr = fileManager::getFileAudio(obj);
            if(ptr) cInPrestito.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="videoD"){
            videoD* ptr = fileManager::getVideoD(obj);
            if(ptr) cInPrestito.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="fileVideo"){
            fileVideo* ptr = fileManager::getFileVideo(obj);
            if(ptr) cInPrestito.push_back(ptr);
        }
    }

    QJsonArray sInPoss = root["sInPossesso"].toArray();
    for(auto it=sInPoss.begin(); it!=sInPoss.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="CD"){
            cd* ptr = fileManager::getCD(obj);
            if(ptr) sInPossesso.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="DVD"){
            dvd* ptr = fileManager::getDVD(obj);
            if(ptr) sInPossesso.push_back(ptr);
        }
    }

    QJsonArray sInPres = root["sInPrestito"].toArray();
    for(auto it=sInPres.begin(); it!=sInPres.end(); it++){
        QJsonObject obj = (*it).toObject();
        if(obj["tipo"].isString() && obj["tipo"].toString()=="CD"){
            cd* ptr = fileManager::getCD(obj);
            if(ptr) sInPrestito.push_back(ptr);
        }else if(obj["tipo"].isString() && obj["tipo"].toString()=="DVD"){
            dvd* ptr = fileManager::getDVD(obj);
            if(ptr) sInPrestito.push_back(ptr);
        }
    }

}

/*getAudioD - costruisce l'oggetto audioD a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto audioD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
audioD* fileManager::getAudioD(const QJsonObject& o){
    audioD* ret = nullptr;
    if(o["titolo"].isString() && o["stereo"].isString() && 
            o["picPath"].isString() && o["casaProdutrice"].isString() && o["pubblicazione"].isDouble() && 
            o["peso"].isDouble() && o["frequenza"].isDouble() && o["durata"].isDouble() && o["canali"].isDouble()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new audioD(o["titolo"].toString(), o["casaProdutrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["frequenza"].toInt(), o["stereo"].toString().toStdString() == "true", o["canali"].toInt());
            }
    return ret;
}

/*getFileAudio - costruisce l'oggetto fileAudio a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto fileAudio
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
fileAudio* fileManager::getFileAudio(const QJsonObject& o){
    fileAudio* ret = nullptr;
    if(o["titolo"].isString() && o["stereo"].isString() && 
            o["picPath"].isString() && o["casaProdutrice"].isString() && o["pubblicazione"].isDouble() && 
            o["lossy"].isString() && o["estensione"].isString() && o["peso"].isDouble() && 
            o["frequenza"].isDouble() && o["durata"].isDouble() && o["canali"].isDouble()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new fileAudio(o["titolo"].toString(), o["casaProdutrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["frequenza"].toInt(), o["stereo"].toString().toStdString() == "true", o["canali"].toInt(), o["lossy"].toString().toStdString() == "true", o["estensione"].toString());
            }
    return ret;
}

/*getVideoD - costruisce l'oggetto videoD a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto videoD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
videoD* fileManager::getVideoD(const QJsonObject& o){
    videoD* ret = nullptr;
    if(o["titolo"].isString() && 
            o["picPath"].isString() && o["casaProdutrice"].isString() && o["pubblicazione"].isDouble() && 
            o["progressivo"].isString() && o["risoluzione"].isString() && o["peso"].isDouble() && 
            o["durata"].isDouble() && o["fps"].isDouble()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new videoD(o["titolo"].toString(), o["casaProdutrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["fps"].toInt(), o["progressivo"].toString().toStdString() == "true", o["risoluzione"].toString());
            }
        return ret;
}

/*getFileVideo - costruisce l'oggetto fileVideo a partire dalla sua serializzazione in json
@param o oggetto json da cui costruire l'oggetto fileVideo
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
fileVideo* fileManager::getFileVideo(const QJsonObject& o){
    fileVideo* ret = nullptr;
    if(o["titolo"].isString() && 
            o["picPath"].isString() && o["casaProdutrice"].isString() && o["pubblicazione"].isDouble() && 
            o["progressivo"].isString() && o["risoluzione"].isString() && o["peso"].isDouble() && 
            o["durata"].isDouble() && o["fps"].isDouble() && o["estensione"].isString()){
                vector<QString> autori;
                int num=0;
                while(o.contains(QString("autore%1").arg(num)) && o[QString("autore%1").arg(num)].isString()){
                    autori.push_back(o[QString("autore%1").arg(num)].toString());
                    num++;
                }
                ret = new fileVideo(o["titolo"].toString(), o["casaProdutrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), o["peso"].toDouble(), o["fps"].toInt(), o["progressivo"].toString().toStdString() == "true", o["risoluzione"].toString(), o["estensione"].toString());
            }
        return ret;
}

/*getCD - costruisce l'oggetto CD a partire dalla sua serializzazione in Json
@param o serializzazione json dell'oggetto CD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
cd* fileManager::getCD(const QJsonObject& o){
    cd* ret = nullptr;
    if(o["diametro"].isDouble()){
        vector<audioD*> tracceAudio;
        QJsonArray tracce = o["tracce"].toArray();
        for(auto it = tracce.begin(); it!=tracce.end(); it++){
            if((*it).isObject()){
                audioD* ptr = fileManager::getAudioD((*it).toObject());
                if(ptr) tracceAudio.push_back(ptr);
            }
        }
        ret = new cd(tracceAudio, o["diametro"].toDouble());
    }
    return ret;
}

/*getDVD - costruisce l'oggetto DVD a partire dalla sua serializzazione in Json
@param o serializzazione json dell'oggetto DVD
@return il puntatore all'oggetto costruito, nullptr altrimenti*/
dvd* fileManager::getDVD(const QJsonObject& o){
    dvd* ret = nullptr;
    if(o["diametro"].isDouble()){
        vector<videoD*> tracceVideo;
        QJsonArray tracce = o["tracce"].toArray();
        for(auto it = tracce.begin(); it!=tracce.end(); it++){
            if((*it).isObject()){
                videoD* ptr = fileManager::getVideoD((*it).toObject());
                if(ptr) tracceVideo.push_back(ptr);
            }
        }
        ret = new dvd(tracceVideo, o["diametro"].toDouble());
    }
    return ret;
}