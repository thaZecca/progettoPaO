#include "include/ModificaContenutoView.hpp"

/*Costruttore parametrico di ModificaContenutoView
@param c puntatore al contenutoMultimediale da modificare
@param parent QWidget parent*/
ModificaContenutoView::ModificaContenutoView(contenutoMultimediale* c, QWidget* parent): QWidget(parent), ptr(c), bottom(nullptr), fd(nullptr), picSelect(nullptr), titolo(nullptr), autori(nullptr), 
    casaProd(nullptr), anno(nullptr), durata(nullptr), scaffale(nullptr),
    freqCamp(nullptr), stereo(nullptr), numeroCanali(nullptr), lossy(nullptr),
    estensione(nullptr), fps(nullptr), progressivo(nullptr), risoluzione(nullptr){

        mainLayout = new QVBoxLayout(this);

        QWidget* contenuto = new QWidget();
        QHBoxLayout* contenutoLayout = new QHBoxLayout(contenuto);
        picSelect = new QPushButton(QPixmap(biblioteca::projectPath().filePath("src/import.png")), "");
        contenutoLayout -> addWidget(picSelect);

        QWidget* info = new QWidget();
        QGridLayout* infoLayout = new QGridLayout(info);
        infoLayout -> addWidget(new QLabel("Titolo:"),0,0);
        titolo = new QLineEdit();
        titolo -> setText(c->getTitolo());
        infoLayout -> addWidget(titolo,0,1);
        infoLayout -> addWidget(new QLabel("Autori:"),1,0);
        autori = new QLineEdit();
        QString a("");
        for(auto i : c->getAutori()){
            a += i +", ";
        }
        a.chop(1); a.chop(1);
        autori -> setText(a);
        autori -> setPlaceholderText(", per separare gli autori");
        infoLayout -> addWidget(autori,1,1);
        infoLayout -> addWidget(new QLabel("Casa produttrice:"),2,0);
        casaProd = new QLineEdit();
        casaProd -> setText(c->getCasaProduttrice());
        infoLayout -> addWidget(casaProd,2,1);
        infoLayout -> addWidget(new QLabel("Anno:"),3,0);
        anno = new QLineEdit();
        anno -> setText(QString::number(c->getAnnoDiPubblicazione()));
        infoLayout -> addWidget(anno);
        infoLayout -> addWidget(new QLabel("Durata:"),1,2);

        int min = c -> getDurataSecondi()/60;
        int sec = c -> getDurataSecondi()%60;

        durata = new QDateTimeEdit();
        durata -> setDisplayFormat("mm:ss");
        durata -> setTime(QTime(0,min,sec));
        infoLayout -> addWidget(durata,1,3);
        infoLayout -> addWidget(new QLabel("Scaffale:"),2,2);
        scaffale = new QLineEdit();
        scaffale -> setText(c->getScaffale());
        infoLayout -> addWidget(scaffale,2,3);

        contenutoLayout -> addWidget(info);
        mainLayout -> addWidget(contenuto);

        if(dynamic_cast<fileAudio*>(ptr)) bottomFileAudio();
        else if(dynamic_cast<audioD*>(ptr)) bottomAudioD();
        else if(dynamic_cast<fileVideo*>(ptr)) bottomFileVideo();
        else if(dynamic_cast<videoD*>(ptr)) bottomVideoD();
        
        cancella = new QPushButton("Cancella");
        salva = new QPushButton("Salva");


        QHBoxLayout* pulsantiLayout = new QHBoxLayout();
        pulsantiLayout -> addWidget(cancella);
        pulsantiLayout -> addWidget(salva);
        mainLayout -> addLayout(pulsantiLayout);

        connect(picSelect, &QPushButton::clicked, this, &ModificaContenutoView::choose_picture);
        connect(cancella, &QPushButton::clicked, this, &ModificaContenutoView::cancel_event);
        connect(salva, &QPushButton::clicked, this, &ModificaContenutoView::save);
}

/*bottomAudioD - prepara la bottom interface con i campi di audioD*/
void ModificaContenutoView::bottomAudioD(){
    audioD* a = dynamic_cast<audioD*>(ptr);
    bottom = new QWidget();
    QGridLayout* bottomLayout = new QGridLayout(bottom);

    freqCamp = new QLineEdit();
    freqCamp -> setText(QString::number(a -> getFrequenzaCampionamento()));
    bottomLayout -> addWidget(new QLabel("Frequenza:"),0,0);
    bottomLayout -> addWidget(freqCamp,0,1);

    stereo = new QCheckBox("Stereo");
    stereo -> setChecked(a -> isStereo());
    bottomLayout -> addWidget(new QLabel("Panorama:"),1,0);
    bottomLayout -> addWidget(stereo,1,1);

    numeroCanali = new QSpinBox();
    numeroCanali -> setValue(a -> getNumeroCanali());
    bottomLayout -> addWidget(new QLabel("Numero canali audio:"),2,0);
    bottomLayout -> addWidget(numeroCanali,2,1);
        
    mainLayout -> addWidget(bottom);
}

/*bottomFileAudio - prepara la bottom interface con i campi di fileAudio*/
void ModificaContenutoView::bottomFileAudio(){
    fileAudio* f = dynamic_cast<fileAudio*>(ptr);
    bottomAudioD();
    QGridLayout* bottomLayout = static_cast<QGridLayout*>(bottom -> layout()); //sono certo sia un QGridLayout

    bottomLayout -> addWidget(new QLabel("Lossy:"),3,0);
    lossy = new QCheckBox();
    lossy -> setChecked(f -> isLossy());
    bottomLayout -> addWidget(lossy,3,1);

    bottomLayout -> addWidget(new QLabel("Estensione:"),4,0);
    estensione = new QLineEdit();
    estensione -> setText(f -> getEstensione());
    bottomLayout -> addWidget(estensione);
}

/*bottomVideoD - prepara la bottom interface con i campi di videoD*/
void ModificaContenutoView::bottomVideoD(){
    videoD* v = dynamic_cast<videoD*>(ptr);
    bottom = new QWidget();
    QGridLayout* bottomLayout = new QGridLayout(bottom);

    fps = new QSpinBox();
    fps -> setValue(v -> getFPS());
    bottomLayout -> addWidget(new QLabel("FPS:"),0,0);
    bottomLayout -> addWidget(fps,0,1);

    progressivo = new QCheckBox("Progressivo");
    progressivo -> setChecked(v -> isProgressivo());
    bottomLayout -> addWidget(new QLabel("Scansione:"),1,0);
    bottomLayout -> addWidget(progressivo,1,1);

    risoluzione = new QLineEdit();
    risoluzione -> setText(v -> getRisoluzione());
    bottomLayout -> addWidget(new QLabel("Risoluzione:"),2,0);
    bottomLayout -> addWidget(risoluzione,2,1);
        
    mainLayout -> addWidget(bottom);
}

/*bottomFileVideo - prepara la bottom interface con i campi di fileVideo*/
void ModificaContenutoView::bottomFileVideo(){
    fileVideo* f = dynamic_cast<fileVideo*>(ptr);
    bottomVideoD();
    QGridLayout* bottomLayout = static_cast<QGridLayout*>(bottom -> layout());
    estensione = new QLineEdit();
    estensione -> setText(f -> getEstensione());
    bottomLayout -> addWidget(new QLabel("Estensione:"),3,0);
    bottomLayout -> addWidget(estensione,3,1);
}

/*save - salvataggio delle modifiche*/
void ModificaContenutoView::save(){
    if(check()){
        if(dynamic_cast<fileAudio*>(ptr)) modifyFileAudio();
        else if(dynamic_cast<audioD*>(ptr)) modifyAudioD();
        else if(dynamic_cast<fileVideo*>(ptr)) modifyFileVideo();
        else if(dynamic_cast<videoD*>(ptr)) modifyVideoD();
        emit(cancel_event());
    }else{
        QMessageBox error;
        error.setText("I campi testuali non possono essere vuoti!");
        error.exec();
    }
}

/*modifyAudioD - modifica l'audioD*/
void ModificaContenutoView::modifyAudioD(){
    audioD* aD = static_cast<audioD*>(ptr);
    QDir baseDir(biblioteca::projectPath());
    bool isInt;
    freqCamp -> text().toInt(&isInt);
    vector<QString> aut;
    for(auto a : autori -> text().split(",")){
        if(a[0]==' '){
            a.remove(0,1);
        }
        aut.push_back(a);
    }
    if(isInt){
        aD -> setTitolo(titolo -> text());
        aD -> setAutori(aut);
        aD -> setDurataSecondi(durata -> time().minute()*60 + durata -> time().second());
        aD -> setCasaProdutttrice(casaProd -> text());
        aD -> setScaffale(scaffale -> text());
        aD -> setFrequenzaCampionamento(freqCamp -> text().toInt());
        aD -> setStereo(stereo -> checkState() == Qt::Checked);
        aD -> setNumeroCanali(numeroCanali -> value());
        if(fd!=nullptr && !fd -> selectedFiles().isEmpty()) aD -> setPicPath(baseDir.relativeFilePath(fd -> selectedFiles().first()));
    }else{
        QMessageBox error;
        error.setText("Frequenza non valida!");
        error.exec();
    }
}

/*modifyFileAudio - modifica il fileAudio*/
void ModificaContenutoView::modifyFileAudio(){
    modifyAudioD();
    fileAudio* f = dynamic_cast<fileAudio*>(ptr);
    if(estensione -> text().isEmpty()){
        QMessageBox error;
        error.setText("Il campo estensione non può essere vuoto!");
        error.exec();
    }else{
        f -> setLossy(lossy -> checkState() == Qt::Checked);
        f -> setEstensione(estensione -> text());
    }
}

/*modifyVideoD - modifica il videoD*/
void ModificaContenutoView::modifyVideoD(){
    videoD* vD = static_cast<videoD*>(ptr);
    QDir baseDir(biblioteca::projectPath());
    vector<QString> aut;
    for(auto a : autori -> text().split(",")){
        if(a[0]==' '){
            a.remove(0,1);
        }
        aut.push_back(a);
    }
    if(!risoluzione -> text().isEmpty()){
        vD -> setTitolo(titolo -> text());
        vD -> setAutori(aut);
        vD -> setDurataSecondi(durata -> time().minute()*60 + durata -> time().second());
        vD -> setCasaProdutttrice(casaProd -> text());
        vD -> setScaffale(scaffale -> text());
        vD -> setFPS(fps -> value());
        vD -> setProgressivo(progressivo -> checkState() == Qt::Checked);
        vD -> setRisoluzione(risoluzione -> text());
        if(fd!=nullptr && !fd -> selectedFiles().isEmpty()) vD -> setPicPath(baseDir.relativeFilePath(fd -> selectedFiles().first()));
    }else{
        QMessageBox error;
        error.setText("Il campo risoluzione non può essere vuoto!");
        error.exec();
    }
}

/*modifyFileVide - modifica il fileVideo*/
void ModificaContenutoView::modifyFileVideo(){
    modifyVideoD();
    fileVideo* f = dynamic_cast<fileVideo*>(ptr);
    if(!estensione -> text().isEmpty()){
        f -> setEstensione(estensione -> text());
    }else{
        QMessageBox error;
        error.setText("Il campo estensione non può essere vuoto!");
        error.exec();
    }
}

/*check - controllo primario sui campi di contenutoMultimediale*/
bool ModificaContenutoView::check(){
    bool a;
    anno -> text().toInt(&a);
    return !titolo -> text().isEmpty() && !autori -> text().isEmpty() && !casaProd -> text().isEmpty() && a 
        && !scaffale -> text().isEmpty();
}

/*chose_picture - seleziona la nuova imagine*/
void ModificaContenutoView::choose_picture(){
    fd = new QFileDialog(this);
    fd -> setFileMode(QFileDialog::ExistingFile); //il file deve esistere e deve essere unico
    fd -> setNameFilter(tr("Images (*.png *.xpm *.jpg)")); //il file deve essere di tipo immagine
    fd -> setDirectory(biblioteca::projectPath()); //deve cercarlo dove si trova il progetto
    fd -> exec();
}