#include "./include/fileManager.hpp"

fileManager::fileManager(){
    QString path = QCoreApplication::applicationDirPath() + "/storage.json";
    QFile file(path);
    std::cout << path.toStdString() << std::endl;
}

fileManager::fileManager(QString path): file(path) {std::cout<< "ciaooo2";} 

void fileManager::save(const vector<contenutoMultimediale*>& contenuti, const vector<contenutoMultimediale*>& prestati){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cerr << ("\n\n\nCouldn't find the file.\n\n\n");
        return;
    }
    std::cout << "ciao3" << std::endl;
    QJsonArray arr;
    JSONvisitor visitor;
    for(auto it=contenuti.begin(); it!=contenuti.end(); it++){
        (*it) -> accept(visitor);
        arr.append(visitor.getJson());
    }
    QJsonDocument doc(arr);
    file.write(doc.toJson());
    std::cout << arr.empty() << std::endl;
    std::cout << doc.isEmpty() << std::endl;
    file.close();
    std::cout << doc.toJson().toStdString() << std::endl;
}

void fileManager::load(vector<contenutoMultimediale*>& contenuti, vector<contenutoMultimediale*>& prestati){

}