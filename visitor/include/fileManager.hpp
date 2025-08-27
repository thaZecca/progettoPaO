#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "../../model/include/audioD.hpp"
#include "../../model/include/fileAudio.hpp"
#include "JSONvisitor.hpp"
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QCoreApplication>


class fileManager{
private:
    QFile file;
    static audioD* getAudioD(const QJsonObject&);
    static videoD* getVideoD(const QJsonObject&);
    static fileAudio* getFileAudio(const QJsonObject&);
    static fileVideo* getFileVideo(const QJsonObject&);
public:
    fileManager(QString);
    void save(const vector<contenutoMultimediale*>&, const vector<contenutoMultimediale*>&, const vector<supportoMultimediale*>&, const vector<supportoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<contenutoMultimediale*>&, vector<supportoMultimediale*>&, vector<supportoMultimediale*>&);
};

#endif