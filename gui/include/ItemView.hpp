#ifndef ITEM_VIEW_HPP
#define ITEM_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include "../../model/include/query.hpp"
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"

class ItemView: public QScrollArea{
    Q_OBJECT 
private:
    void filter(query* q, vector<contenutoMultimediale*>&, vector<supportoMultimediale*>&);
public:
    explicit ItemView(QWidget* parent =nullptr);
    void prepare(query* =nullptr);
public slots:
    void submitQuery(query q);
};

#endif