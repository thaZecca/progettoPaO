#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include <string>
#include <QJsonDocument>

class fileManager{
private:
    QFile file;
public:
    fileManager();
    fileManager(string);
    void save(const vector<contenutoMultimediale*>&, const vector<contenutoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<contenutoMultimediale*>&);
};

#endif