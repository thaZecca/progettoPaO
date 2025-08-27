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
            std::cout << *(fileManager::getAudioD(obj)) << std::endl ;
        }
    }
}

audioD* fileManager::getAudioD(QJsonObject& o){
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
                ret = new audioD(o["titolo"].toString(), o["casaProdutrice"].toString(), autori, o["pubblicazione"].toInt(), o["durata"].toInt(), o["picPath"].toString(), static_cast<float>(o["peso"].toDouble()), o["frequenza"].toInt(), o["stereo"].toString().toStdString() == "true", o["canali"].toInt());
            }
    return ret;
}