#ifndef ADD_OBJECT_VIEW_HPP
#define ADD_OBJECT_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QSize>
#include <QLayoutItem>
#include "../../fileManager/include/biblioteca.hpp"
#include "AddContenutoView.hpp"

class AddObjectView: public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    AddContenutoView* addContenuto;
    QPushButton* selectContenuto;
    QPushButton* selectSupporto;
    QPushButton* indietro;
public:
    explicit AddObjectView(QWidget* parent =nullptr);
signals:
    void back_event();
public slots:
    void add_contenuto();
};

#endif