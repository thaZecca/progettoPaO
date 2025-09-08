#include "include/AddObjectView.hpp"

AddObjectView::AddObjectView(QWidget* parent): QWidget(parent), addContenuto(nullptr){
    mainLayout = new QVBoxLayout(this);

    QLabel* text = new QLabel("Che tipo di ogggetto vuoi aggiungere?");
    mainLayout -> addWidget(text, 0, Qt::AlignCenter);

    QWidget* chooseWidget = new QWidget();
    QHBoxLayout* chooseLayout = new QHBoxLayout(chooseWidget);
    selectContenuto = new QPushButton(QPixmap(biblioteca::projectPath().filePath("src/contenutoMultimediale.png")), "");
    selectContenuto -> setFlat(true);
    selectContenuto -> setFixedSize(100,100);
    selectContenuto -> setIconSize(QSize(100,100));
    chooseLayout -> addWidget(selectContenuto);
    selectSupporto = new QPushButton(QPixmap(biblioteca::projectPath().filePath("src/supportoMultimediale.png")), "");
    selectSupporto -> setFlat(true);
    selectSupporto -> setFixedSize(100,100);
    selectSupporto -> setIconSize(QSize(100,100));
    chooseLayout -> addWidget(selectSupporto);
    mainLayout -> addWidget(chooseWidget);

    indietro = new QPushButton("Indietro");
    mainLayout -> addWidget(indietro, 0, Qt::AlignCenter | Qt::AlignBottom);

    connect(indietro, &QPushButton::clicked, this, &AddObjectView::back_event);
    connect(selectContenuto, &QPushButton::clicked, this, &AddObjectView::add_contenuto);
}

void AddObjectView::add_contenuto(){
    QLayoutItem* item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            delete widget;  // distrugge il widget
        }
        delete item;
    }
    addContenuto = new AddContenutoView();
    mainLayout -> addWidget(addContenuto);
    connect(addContenuto, &AddContenutoView::cancel_event, this, &AddObjectView::back_event);
}