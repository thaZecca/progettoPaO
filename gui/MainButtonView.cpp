#include "include/MainButtonView.hpp"

MainButtonView::MainButtonView(QWidget* parent): QWidget(parent){
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    add = new QPushButton();
    add -> setText("Add");
    
    remove = new QPushButton();
    remove -> setText("Remove");

    save = new QPushButton();
    save -> setText("Save");

    reload = new QPushButton();
    reload -> setText("Reload");

    mainLayout -> addWidget(add);
    mainLayout -> addWidget(remove);
    mainLayout -> addWidget(save);
    mainLayout -> addWidget(reload);

    //signal forwarding dei pulsanti
    connect(save, &QPushButton::clicked, this, &MainButtonView::save_event);
    connect(reload, &QPushButton::clicked, this, &MainButtonView::reload_event);
    connect(add, &QPushButton::clicked, this, &MainButtonView::add_event);
}