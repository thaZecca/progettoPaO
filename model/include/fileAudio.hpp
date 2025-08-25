#ifndef FILEAUDIO_HPP
#define FILEAUDIO_HPP

#include "audioD.hpp"

class fileAudio: public audioD{
    friend ostream& operator<<(ostream&, const fileAudio&);
private:
    bool lossy;
    QString estensione;
public:
    fileAudio(QString, QString, vector<QString>, unsigned int, unsigned int, QString, float, unsigned int, bool, unsigned int, bool, QString);
    bool isLossy() const;
    QString getEstensione() const;
    void setLossy(bool);
    void setEstensione(QString);
    virtual void accept(visitorCMultimediale&) override;
};

ostream& operator<<(ostream&, const fileAudio&);

#endif