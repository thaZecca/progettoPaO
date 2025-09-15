#ifndef SUPP_MULT_HPP
#define SUPP_MULT_HPP

#include "digitale.hpp"
#include "../../visitor/include/visitorCMultimediale.hpp"
#include <vector>
#include <iostream>

using std::vector;

class supportoMultimediale{
    friend ostream& operator<<(ostream&, const supportoMultimediale&);
private:
    QString titolo;
    QString scaffale;
public:
    supportoMultimediale(const QString& s, const QString& t);
    virtual ~supportoMultimediale() = default;
    virtual vector<contenutoMultimediale*> getTracce() const = 0;
    virtual void setTracce(const vector<contenutoMultimediale*>&) = 0;
    virtual void accept(visitorCMultimediale&) = 0;
    QString getTitolo() const;
    void setTitolo(const QString& t);
    virtual vector<QString> getAutori() const = 0;
    virtual vector<int> getAnno() const = 0;
    virtual int getDiametro() const = 0;
    virtual void setDiametro(int) = 0;
    QString getScaffale() const;
    void setScaffale(const QString&);
};

ostream& operator<<(ostream&, const supportoMultimediale&);

#endif