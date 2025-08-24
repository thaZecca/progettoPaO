#ifndef CONT_MULT_HPP
#define CONT_MULT_HPP

#include <QString>
#include <vector>
#include <iostream>
#include "../visitor/visitorCMultimediale.hpp"

using std::vector;
using std::ostream;

class contenutoMultimediale{
    friend ostream& operator<<(ostream&, const contenutoMultimediale&);
private:
    QString titolo;
    QString casaProduttrice;
    vector<QString> autori;
    unsigned int annoDiPubblicazione;
    unsigned int durataSecondi;
    QString picPath;
public:
    contenutoMultimediale(QString, QString, vector<QString>, unsigned int, unsigned int, QString);
    virtual ~contenutoMultimediale() = 0;
    QString getTitolo() const;
    QString getCasaProduttrice() const;
    vector<QString> getAutori() const;
    unsigned int getAnnoDiPubblicazione() const;
    unsigned int getDurataSecondi() const;
    QString getPicPath() const;
    void setTitolo(const QString& t);
    void setCasaProdutttrice(const QString& cP);
    void setAutori(const vector<QString>& a);
    void setAutore(unsigned int p, const QString& a);
    void setAnnoDiPubblicazione(unsigned int aDPubb);
    void setDurataSecondi(unsigned int d);
    void setPicPath(const QString& pP);
    virtual void accept(const visitorCMultimediale& v) = 0;
};

ostream& operator<<(ostream&, const contenutoMultimediale&);

#endif