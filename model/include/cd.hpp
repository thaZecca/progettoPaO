#ifndef CD_HPP
#define CD_HPP

#include <vector>
#include <iostream>
#include "./audioD.hpp"
#include "./supportoMultimediale.hpp"

using std::vector;

class cd: public supportoMultimediale{
    friend ostream& operator<<(ostream&, const cd&);
private:
    vector<audioD*> tracceAudio;
    float diametro;
public:
    cd(vector<audioD*>, float, QString, QString);
    vector<contenutoMultimediale*> getTracce() const override;
    float getDiametro() const;
    void setTracce(const vector<contenutoMultimediale*>&) override;
    void setDiametro(float);
    virtual void accept(visitorCMultimediale&) override;
};

ostream& operator<<(ostream&, const cd&);

#endif