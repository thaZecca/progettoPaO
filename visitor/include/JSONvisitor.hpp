#ifndef JSONVISITOR_HPP
#define JSONVISITOR_HPP

#include <QJsonDocument>
#include "../visitorCMultimediale.hpp"

class JSONVisitor{
private:
    QJsonObject jsonMedia;
public:
    void visitAudioD(const audioD&) override;
    void visitFileAudio(const fileAudio&) override;
    void visitCD(const cd&) override;
    void visitVideoD(const videoD&) override;
    void visitFileVideo(const fileVideo&) override;
    void visitDVD(const dvd&) override;
};

#endif