#ifndef JSONVISITOR_HPP
#define JSONVISITOR_HPP

#include <QJsonObject>
#include <QString>
#include <vector>
#include "../visitorCMultimediale.hpp"

class digitale;

using std::vector;

class JSONvisitor: public visitorCMultimediale{
private:
    QJsonObject jsonMedia;
    vector<QJsonObject> jsonMore;
    void toJsonCM(const contenutoMultimediale*);
    void toJsonDig(const digitale*);
public:
    void visitAudioD(audioD*) override;
    void visitFileAudio(fileAudio*) override;
    void visitCD(cd*) override;
    void visitVideoD(videoD*) override;
    void visitFileVideo(fileVideo*) override;
    void visitDVD(dvd*) override;
    QJsonObject& getJson() const;
    vector<QJsonObject>& getJsonMore() const;
};

#endif