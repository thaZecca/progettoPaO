#ifndef FULL_PREVIEW_HPP
#define FULL_PREVIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include "../../model/include/query.hpp"
#include "../../fileManager/include/biblioteca.hpp"

class FullPreview: public QWidget{
    Q_OBJECT
private:
    QLabel* picture;
    QLabel* title;
    QLabel* artists;
    QLabel* year;
    Qlabel* logo;
    QPushButton* presta;
    QPushButton* back;
    QPushButton* modifica;

public:
    explicit FullPreview(int ip, query* q, QWidget* parent =nullptr);
};

#endif