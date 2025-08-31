#ifndef ITEM_VIEW_HPP
#define ITEM_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <vector>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"

using std::vector;

class ItemView: public QScrollArea{
    Q_OBJECT
public:
    explicit ItemView(QWidget* parent =nullptr);
};

#endif