#include "include/SearchView.hpp"

/*Costruttore parametrico di SearchView
@param parent QWidget parent*/
SearchView::SearchView(QWidget* parent): QGroupBox("Cerca",parent){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    src = new QLineEdit();
    src -> setPlaceholderText("Cerca");
    mainLayout -> addWidget(src);

    QWidget* type = new QWidget();
    QVBoxLayout* typeLayout = new QVBoxLayout(type);
    radioGroup = new QButtonGroup(this);

    all = new QRadioButton("Tutti");
    all -> setChecked(true);
    radioGroup -> addButton(all);
    isAudioD = new QRadioButton("Audio digitale");
    radioGroup -> addButton(isAudioD);
    isCD = new QRadioButton("CD");
    radioGroup -> addButton(isCD);
    isDVD = new QRadioButton("DVD");
    radioGroup -> addButton(isDVD);
    isFileA = new QRadioButton("File Audio");
    radioGroup -> addButton(isFileA);
    isFileV = new QRadioButton("File Video");
    radioGroup -> addButton(isFileV);
    isVideoD = new QRadioButton("Video digitale");
    radioGroup -> addButton(isVideoD);

    typeLayout -> addWidget(all);
    typeLayout -> addWidget(isAudioD);
    typeLayout -> addWidget(isCD);
    typeLayout -> addWidget(isDVD);
    typeLayout -> addWidget(isFileA);
    typeLayout -> addWidget(isFileV);
    typeLayout -> addWidget(isVideoD);

    searchTitle = new QCheckBox("Titolo");
    searchArtist = new QCheckBox("Artista");
    searchYear = new QCheckBox("Anno");

    QWidget* searchCheck = new QWidget();
    QVBoxLayout* searchLayout = new QVBoxLayout(searchCheck);

    searchLayout -> addWidget(searchTitle);
    searchLayout -> addWidget(searchArtist);
    searchLayout -> addWidget(searchYear);

    QWidget* filter = new QWidget();
    QHBoxLayout* filterLayout = new QHBoxLayout(filter);

    filterLayout -> addWidget(type);
    filterLayout -> addWidget(searchCheck);

    mainLayout -> addWidget(filter);

    go = new QPushButton("Cerca");
    mainLayout -> addWidget(go);

    /*Connessione pulsante cerca-segnale*/
    connect(go, &QPushButton::clicked, this, &SearchView::search);
}

/*search - trae le informazioni e fa partire la ricerca*/
void SearchView::search(){
    query q(src->text(), (radioGroup->checkedButton())->text(), searchTitle -> isChecked(), searchArtist -> isChecked(), searchYear -> isChecked());
    emit(search_event(q));
}