#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QFile>
#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "../../model/include/audioD.hpp"
#include "../../model/include/fileAudio.hpp"
#include "../../model/include/videoD.hpp"
#include "../../model/include/fileVideo.hpp"
#include "../../model/include/cd.hpp"
#include "../../model/include/dvd.hpp"
#include "../../visitor/include/JSONvisitor.hpp"
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
    static cd* getCD(const QJsonObject&);
    static dvd* getDVD(const QJsonObject&);
public:
    fileManager(QString);
    void save(const vector<contenutoMultimediale*>&, const vector<supportoMultimediale*>&);
    void load(vector<contenutoMultimediale*>&, vector<supportoMultimediale*>&);
};

#endif