#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "../../model/include/audioD.hpp"
#include "JSONvisitor.hpp"
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QCoreApplication>


class fileManager{
private:
    QFile file;
    static audioD* getAudioD(QJsonObject&);
    static videoD* getVideoD(QJsonObject&);
    static fileAudio* getFileAudio(QJsonObject&);
    static fileVideo* getFileVideo(QJsonObject&);
public:
    fileManager(QString);
    void save(const vector<contenutoMultimediale*>&, const vector<contenutoMultimediale*>&, const vector<supportoMultimediale*>&, const vector<supportoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<contenutoMultimediale*>&, vector<supportoMultimediale*>&, vector<supportoMultimediale*>&);
};

#endif