#include "./include/fileManager.hpp"

fileManager::fileManager(QString path): file(path) {} 

void fileManager::save(const vector<contenutoMultimediale*>& cInPossesso, const vector<contenutoMultimediale*>& cInPrestito, const vector<supportoMultimediale*>& sInPossesso, const vector<supportoMultimediale*>& sInPrestito){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cerr << ("\n\n\nCouldn't find the file.\n\n\n");
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

void fileManager::load(vector<contenutoMultimediale*>& contenuti, vector<contenutoMultimediale*>& prestati){

}