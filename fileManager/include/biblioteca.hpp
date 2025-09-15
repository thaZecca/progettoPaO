#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <vector>
#include "../../model/include/contenutoMultimediale.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "fileManager.hpp"
#include "../../model/include/query.hpp"
#include <QString>
#include <QApplication>
#include <QDir>

class biblioteca{
private:
    static biblioteca* _instance;
    biblioteca(QString path);
    ~biblioteca();
    biblioteca(const biblioteca&) = delete;
    biblioteca& operator=(const biblioteca&) = delete;
    fileManager& getFileManager();
    vector<contenutoMultimediale*> contenuti;
    vector<supportoMultimediale*> supporti;
    fileManager fM;
    static QString storage_path;
public:
    static biblioteca& instance();  
    static void init(const QString& path);
    static QDir projectPath();
    vector<contenutoMultimediale*>& getContenuti();
    vector<supportoMultimediale*>& getSupporti();
    void save();
    void load();
    static contenutoMultimediale* cSearch(int pos, vector<contenutoMultimediale*>& c);
    static supportoMultimediale* sSearch(int pos, vector<contenutoMultimediale*>& c, vector<supportoMultimediale*>& s);
    static void add(contenutoMultimediale*);
    static void add(supportoMultimediale*);
    void remove(int, query*);
    static QString getStoragePath();
};

#endif