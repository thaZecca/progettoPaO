#ifndef SUPP_MULT_HPP
#define SUPP_MULT_HPP

#include "digitale.hpp"
#include "../../visitor/include/visitorCMultimediale.hpp"
#include <vector>

using std::vector;

class supportoMultimediale{
private:
    QString scaffale;
    bool inPrestito;
    QDate dataPrestito;
    int durataPrestito;
    QString nomePrestito;
public:
    supportoMultimediale(const QString& s);
    virtual vector<contenutoMultimediale*> getTracce() const = 0;
    virtual void setTracce(const vector<contenutoMultimediale*>&) = 0;
    virtual void accept(visitorCMultimediale&) = 0;
    
    //sistema bibliotecario

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

#endif