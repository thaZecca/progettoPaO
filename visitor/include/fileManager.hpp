#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "JSONvisitor.hpp"
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>


class fileManager{
private:
    QFile file;
public:
    fileManager();
    fileManager(QString);
    void save(const vector<contenutoMultimediale*>&, const vector<contenutoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<contenutoMultimediale*>&);
};

#endif