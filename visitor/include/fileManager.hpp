#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "JSONvisitor.hpp"
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>


class fileManager{
private:
    QFile file;
public:
    fileManager(QString);
    void save(const vector<contenutoMultimediale*>&, const vector<contenutoMultimediale*>&, const vector<supportoMultimediale*>&, const vector<supportoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<contenutoMultimediale*>&);
};

#endif