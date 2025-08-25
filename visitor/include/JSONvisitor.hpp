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
    void visit(audioD*) override;
    void visit(fileAudio*) override;
    void visit(cd*) override;
    void visit(videoD*) override;
    void visit(fileVideo*) override;
    void visit(dvd*) override;
    QJsonObject& getJson() const;
    vector<QJsonObject>& getJsonMore() const;
};

#endif