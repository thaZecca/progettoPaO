#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "fileManager.hpp"
#include <QString>
#include <QApplication>
#include <QDir>

class biblioteca{
private:
    biblioteca(QString path);
    ~biblioteca();
    biblioteca(const biblioteca&) = delete;
    biblioteca& operator=(const biblioteca&) = delete;
    fileManager& getFileManager();
    vector<contenutoMultimediale*> contenuti;
    vector<supportoMultimediale*> supporti;
    fileManager fM;
public:
    static biblioteca& instance();  
    static QDir projectPath();
    vector<contenutoMultimediale*>& getContenuti();
    vector<supportoMultimediale*>& getSupporti();
    static void presta(contenutoMultimediale*, QString, QDate, int);
    static void presta(supportoMultimediale*, QString, QDate, int);
    static void rientra(contenutoMultimediale*);
    static void rientra(supportoMultimediale*);
};

#endif