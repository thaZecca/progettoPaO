#include "include/MainWindow.hpp"

/*Costruttore parametrico di MainWindow*/
MainWindow::MainWindow(QWidget* parent): QWidget(parent){
    resize(1050, 700); // Imposta la dimensione iniziale della finestra
    setMinimumSize(600, 400); // Imposta la dimensione minima
    ItemView* previews = new ItemView();
    StatView* statistics = new StatView();
    SearchView* search = new SearchView();
    MainButtonView* buttons = new MainButtonView();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout -> addWidget(previews);

    QWidget* right = new QWidget();
    right -> setMaximumWidth(330);
    QVBoxLayout* rightLayout = new QVBoxLayout(right);
    rightLayout -> addWidget(statistics);
    rightLayout -> addWidget(search);
    rightLayout -> addWidget(buttons);

    mainLayout -> addWidget(right);

    //Connessioni tra segnali e slots delle classi
    connect(search, &SearchView::search_event, previews, &ItemView::submitQuery);
} 