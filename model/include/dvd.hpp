#ifndef DVD_HPP
#define DVD_HPP

#include <iostream>
#include <vector>
#include "./videoD.hpp"

using std::vector;

class dvd{
    friend ostream& operator<<(ostream&, const dvd&);
private:
    vector<videoD> tracceVideo;
    float diametro;
public:
    dvd(vector<videoD>, float);
    vector<videoD> getTracceVideo() const;
    float getDiametro() const;
    void setTracceVideo(vector<videoD>&);
    void setDiametro(float d); 
    virtual void accept(visitorCMultimediale&);
};

ostream& operator<<(ostream&, const dvd&);

#endif