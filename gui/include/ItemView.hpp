#ifndef ITEM_VIEW_HPP
#define ITEM_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QString>
#include "ClickablePreview.hpp"
#include "../../model/include/query.hpp"
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"

class ItemView: public QScrollArea{
    Q_OBJECT 
private:
    query* lastQuery;
public:
    explicit ItemView(QWidget* parent =nullptr);
    void prepare(query* =nullptr);
    query* getLastQuery() const;
signals:
    void clicked(int ip);
public slots:
    void submitQuery(query q);
    void reload_preview();
    void click_preview_event(int ip);
};

#endif