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
    cd(vector<audioD*>, float);
    vector<contenutoMultimediale*> getTracce() const;
    float getDiametro() const;
    void setTracce(const vector<contenutoMultimediale*>&);
    void setDiametro(float);
    virtual void accept(visitorCMultimediale&);
};

ostream& operator<<(ostream&, const cd&);

#endif