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
    int diametro;
public:
    dvd(vector<videoD*>, int, QString, QString);
    vector<contenutoMultimediale*> getTracce() const override; 
    int getDiametro() const override;
    void setTracce(const vector<contenutoMultimediale*>&) override;
    void setDiametro(int) override; 
    virtual void accept(visitorCMultimediale&) override;
    virtual vector<QString> getAutori() const override;
    virtual vector<int> getAnno() const override;
};

ostream& operator<<(ostream&, const dvd&);

#endif