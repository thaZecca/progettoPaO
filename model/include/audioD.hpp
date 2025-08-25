#ifndef AUDIOD_HPP
#define AUDIOD_HPP

#include "digitale.hpp"

class audioD: public digitale{
    friend ostream& operator<<(ostream&, const audioD&);
private:
    unsigned int frequenzaCampionamento;
    bool stereo;
    unsigned int numeroCanali;
public:
    audioD(QString, QString, vector<QString>, unsigned int, unsigned int, QString, float, unsigned int, bool, unsigned int);
    virtual ~audioD() override = default;
    unsigned int getFrequenzaCampionamento() const;
    bool isStereo() const;
    unsigned int getNumeroCanali() const;
    void setFrequenzaCampionamento(unsigned int);
    void setStereo(bool);
    void setNumeroCanali(unsigned int);
    void accept(const visitorCMultimediale&) override;
};

ostream& operator<<(ostream&, const audioD&);

#endif