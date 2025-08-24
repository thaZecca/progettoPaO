#include "./include/fileManager.hpp"

fileManager::fileManager(): file("./storage.json") {}

fileManager::fileManager(string path): file(path) {} 

void fileManager::save(const vector<contenutoMultimediale*>& contenuti, const vector<contenutoMultimediale*>& prestati){
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("Couldn't find the file.");
        return;
    }



}

void fileManager::load(vector<contenutoMultimediale*>& contenuti, vector<contenutoMultimediale*>& prestati){

}