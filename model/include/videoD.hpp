#ifndef VIDEOD_HPP
#define VIDEOD_HPP

#include "digitale.hpp"

class videoD: public digitale{
    friend ostream& operator<<(ostream&, const videoD&);
private:
    unsigned int fps;
    bool progressivo;
    QString risoluzione;
public:
    videoD(QString, QString, vector<QString>, unsigned int, unsigned int, QString, float, unsigned int, bool, QString);
    virtual ~videoD() override = default;
    unsigned int getFPS() const;
    bool isProgressivo() const;
    QString getRisoluzione() const;
    void setFPS(unsigned int);
    void setProgressivo(bool);
    void setRisoluzione(QString);
    virtual void accept(const visitorCMultimediale& v) override;
};

ostream& operator<<(ostream&, const videoD&);

#endif