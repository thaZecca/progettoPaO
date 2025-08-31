#ifndef JSONVISITOR_HPP
#define JSONVISITOR_HPP

#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <vector>
#include "./visitorCMultimediale.hpp"

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
    virtual void visit(audioD*) override;
    virtual void visit(fileAudio*) override;
    virtual void visit(cd*) override;
    virtual void visit(videoD*) override;
    virtual void visit(fileVideo*) override;
    virtual void visit(dvd*) override;
    QJsonObject& getJson();
};

#endif