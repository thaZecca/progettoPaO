#ifndef DVD_HPP
#define DVD_HPP

#include <iostream>
#include <vector>
#include "./supportoMultimediale.hpp"
#include "./videoD.hpp"

using std::vector;

class dvd: public supportoMultimediale{
    friend ostream& operator<<(ostream&, const dvd&);
private:
    vector<videoD*> tracceVideo;
    float diametro;
public:
    dvd(vector<videoD*>, float);
    vector<contenutoMultimediale*> getTracce() const override; 
    float getDiametro() const;
    void setTracce(const vector<contenutoMultimediale*>&) override;
    void setDiametro(float d); 
    virtual void accept(visitorCMultimediale&) override;
};

ostream& operator<<(ostream&, const dvd&);

#endif