#ifndef FILEVIDEO_HPP
#define FILEVIDEO_HPP

#include "videoD.hpp"

class fileVideo: public videoD{
    friend ostream& operator<<(ostream&, const fileVideo&);
private:
    QString estensione;
public:
    fileVideo(QString, QString, vector<QString>, unsigned int, unsigned int, QString, float, unsigned int, bool, QString, QString);
    QString getEstensione() const;
    void setEstensione(QString);
    virtual void accept(const visitorCMultimediale&) override;
};

ostream& operator<<(ostream&, const fileVideo&);

#endif