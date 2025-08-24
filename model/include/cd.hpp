#ifndef CD_HPP
#define CD_HPP

#include <vector>
#include <iostream>
#include "./audioD.hpp"

using std::vector;

class cd{
    friend ostream& operator<<(ostream&, const cd&);
private:
    vector<audioD> tracceAudio;
    float diametro;
public:
    cd(vector<audioD>, float);
    vector<audioD> getTracceAudio() const;
    float getDiametro() const;
    void setTracceAudio(vector<audioD>&);
    void setDiametro(float);
};

ostream& operator<<(ostream&, const cd&);

#endif