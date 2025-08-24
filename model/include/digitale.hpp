#ifndef DIGITAL_HPP
#define DIGITAL_HPP

#include "contenutoMultimediale.hpp"

class digitale: public contenutoMultimediale{
    friend ostream& operator<<(ostream&, const digitale&);
private:
    float peso;
public:
    digitale(QString, QString, vector<QString>, unsigned int, unsigned int, QString, float);
    float getPeso() const;
    void setPeso(float);
};

ostream& operator<<(ostream&, const digitale&);

#endif