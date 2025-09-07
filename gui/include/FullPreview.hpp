#ifndef FULL_PREVIEW_HPP
#define FULL_PREVIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../model/include/query.hpp"
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/FullPreviewVisitor.hpp"

class FullPreview: public QWidget{
    Q_OBJECT
private:
    QWidget* multimedia;
    QPushButton* back;
    QPushButton* modifica;
    void prepare(int ip, query* q);
public:
    explicit FullPreview(int ip, query* q, QWidget* parent =nullptr);
signals:
    void back_event();
};

#endif