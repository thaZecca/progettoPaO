#include "./include/fileManager.hpp"

fileManager::fileManager(): file("./storage.json") {}

fileManager::fileManager(QString path): file(path) {} 

void fileManager::save(const vector<contenutoMultimediale*>& contenuti, const vector<contenutoMultimediale*>& prestati){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("Couldn't find the file.");
        return;
    }

    QJsonObject obj;
    JSONvisitor visitor;
    QJsonDocument* doc;
    for(auto it=contenuti.begin(); it!=contenuti.end(); it++){
        *it -> accept(visitor);
        obj = visitor.getJson();
        doc = new QJsonDocument(obj);
        file.write(doc->toJson());
        delete doc;
    }

    file.close();

}

void fileManager::load(vector<contenutoMultimediale*>& contenuti, vector<contenutoMultimediale*>& prestati){

}