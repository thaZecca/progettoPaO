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
    int diametro;
public:
    cd(vector<audioD*>, int, QString, QString);
    vector<contenutoMultimediale*> getTracce() const override;
    int getDiametro() const override;
    void setTracce(const vector<contenutoMultimediale*>&) override;
    void setDiametro(int) override;
    virtual void accept(visitorCMultimediale&) override;
    virtual vector<QString> getAutori() const override;
    virtual vector<int> getAnno() const override;
};

ostream& operator<<(ostream&, const cd&);

#endif