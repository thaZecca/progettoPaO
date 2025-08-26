#ifndef JSONVISITOR_HPP
#define JSONVISITOR_HPP

#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <vector>
#include "../visitorCMultimediale.hpp"

class digitale;
class supportoMultimediale;

using std::vector;

class JSONvisitor: public visitorCMultimediale{
private:
    QJsonObject jsonMedia;
    void toJsonCM(const contenutoMultimediale*);
    void toJsonDig(const digitale*);
    void toJsonSM(const supportoMultimediale*);

public:
    void visit(audioD*) override;
    void visit(fileAudio*) override;
    void visit(cd*) override;
    void visit(videoD*) override;
    void visit(fileVideo*) override;
    void visit(dvd*) override;
    QJsonObject& getJson();
};

#endif