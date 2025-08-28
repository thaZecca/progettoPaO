#ifndef CONT_MULT_HPP
#define CONT_MULT_HPP

#include <QString>
#include <QDate>
#include <vector>
#include <iostream>
#include "../../visitor/include/visitorCMultimediale.hpp"
#include "../../visitor/include/JSONvisitor.hpp"

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
    //parte "sporcata" dalla bibliteca
    QString scaffale;
    bool inPrestito;
    QDate dataPrestito;
    int durataPrestito;
    QString nomePrestito;
public:
    contenutoMultimediale(QString, QString, vector<QString>, unsigned int, unsigned int, QString, QString);
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
    virtual void accept(visitorCMultimediale& v) = 0;
    
    //parte "sporcata" dalla biblioteca

    bool isInPrestito() const;
    void setInPrestito(bool);
    QDate getDataPrestito() const;
    void setDataPrestito(const QDate&);
    int getDurataPrestito() const;
    void setDurataPrestito(int);
    QString getNomePrestito() const;
    void setNomePrestito(const QString&);
    QString getScaffale() const;
    void setScaffale(const QString&);
};

ostream& operator<<(ostream&, const contenutoMultimediale&);

#endif