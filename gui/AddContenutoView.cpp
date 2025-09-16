#include "include/AddContenutoView.hpp"

/*Costruttore parametrico di AddContenutoView
@param s stato di istanziazione: 1 - CD, 2 - DVD, other: normale
@param parent*/
AddContenutoView::AddContenutoView(int s, QWidget* parent): 
    QWidget(parent), ptr(nullptr), state(s), bottom(nullptr), fd(nullptr), picSelect(nullptr), titolo(nullptr), autori(nullptr), 
    casaProd(nullptr), anno(nullptr), durata(nullptr), scaffale(nullptr), tipo(nullptr),
    freqCamp(nullptr), stereo(nullptr), numeroCanali(nullptr), lossy(nullptr),
    estensione(nullptr), fps(nullptr), progressivo(nullptr), risoluzione(nullptr) {
        mainLayout = new QVBoxLayout(this);

        QWidget* contenuto = new QWidget();
        QHBoxLayout* contenutoLayout = new QHBoxLayout(contenuto);
        picSelect = new QPushButton(QPixmap(biblioteca::projectPath().filePath("src/import.png")), "");
        contenutoLayout -> addWidget(picSelect);

        QWidget* info = new QWidget();
        QGridLayout* infoLayout = new QGridLayout(info);
        infoLayout -> addWidget(new QLabel("Titolo:"),0,0);
        titolo = new QLineEdit();
        infoLayout -> addWidget(titolo,0,1);
        infoLayout -> addWidget(new QLabel("Autori:"),1,0);
        autori = new QLineEdit();
        autori -> setPlaceholderText(", per separare gli autori");
        infoLayout -> addWidget(autori,1,1);
        infoLayout -> addWidget(new QLabel("Casa produttrice:"),2,0);
        casaProd = new QLineEdit();
        infoLayout -> addWidget(casaProd,2,1);
        infoLayout -> addWidget(new QLabel("Anno:"),3,0);
        anno = new QLineEdit();
        infoLayout -> addWidget(anno);
        infoLayout -> addWidget(new QLabel("Durata:"),1,2);
        durata = new QDateTimeEdit();
        durata -> setDisplayFormat("mm:ss");
        infoLayout -> addWidget(durata,1,3);
        infoLayout -> addWidget(new QLabel("Scaffale:"),2,2);
        scaffale = new QLineEdit();
        infoLayout -> addWidget(scaffale,2,3);

        contenutoLayout -> addWidget(info);
        mainLayout -> addWidget(contenuto);

        tipo = new QButtonGroup();
        QRadioButton* aD = new QRadioButton("Audio Digitale");
        QRadioButton* fA = new QRadioButton("File Audio");
        QRadioButton* vD = new QRadioButton("Video Digitale");
        QRadioButton* fV = new QRadioButton("File Video");
        tipo -> addButton(aD);
        tipo -> addButton(fA);
        tipo -> addButton(vD);
        tipo -> addButton(fV);
        
        QWidget* widTipo = new QWidget();
        QHBoxLayout* tipoLayout = new QHBoxLayout(widTipo);
        tipoLayout -> addWidget(aD);
        tipoLayout -> addWidget(fA);
        tipoLayout -> addWidget(vD);
        tipoLayout -> addWidget(fV);

        mainLayout -> addWidget(widTipo);

        bottom = new QWidget();
        mainLayout -> addWidget(bottom);
        
        cancella = new QPushButton("Cancella");
        salva = new QPushButton("Salva");


        QHBoxLayout* pulsantiLayout = new QHBoxLayout();
        pulsantiLayout -> addWidget(cancella);
        pulsantiLayout -> addWidget(salva);
        mainLayout -> addLayout(pulsantiLayout);

        connect(tipo, &QButtonGroup::buttonClicked, this, &AddContenutoView::type_event);
        connect(cancella, &QPushButton::clicked, this, &AddContenutoView::cancel_event);
        connect(salva, &QPushButton::clicked, this, &AddContenutoView::save);
        connect(picSelect, &QPushButton::clicked, this, &AddContenutoView::select_image);

        if(s == 1){
            aD -> setChecked(true);
            fA -> setEnabled(false);
            vD -> setEnabled(false);
            fV -> setEnabled(false);
            type_event(aD);
        }else if(s == 2){
            aD -> setEnabled(false);
            fA -> setEnabled(false);
            vD -> setChecked(true);
            fV -> setEnabled(false);
            type_event(vD);
        }
    }

    /*type_event - slot per ridisegnare la bottom interface quando viene selezionato un tipo
    @param b pulsante che ha scatenato l'evento*/
    void AddContenutoView::type_event(QAbstractButton* b){
        if(b -> text() == "Audio Digitale") bottomAudioD();
        else if(b -> text() == "File Audio") bottomFileAudio();
        else if(b -> text() == "Video Digitale") bottomVideoD();
        else if(b -> text() == "File Video") bottomFileVideo();
    }

    /*bottomAudioD - prepara la bottom interface con i campi di audioD*/
    void AddContenutoView::bottomAudioD(){
        delete bottom; //caso sicuro, bottom è amorfo
        bottom = new QWidget();
        QGridLayout* bottomLayout = new QGridLayout(bottom);

        freqCamp = new QLineEdit();
        bottomLayout -> addWidget(new QLabel("Frequenza:"),0,0);
        bottomLayout -> addWidget(freqCamp,0,1);

        stereo = new QCheckBox("Stereo");
        bottomLayout -> addWidget(new QLabel("Panorama:"),1,0);
        bottomLayout -> addWidget(stereo,1,1);

        numeroCanali = new QSpinBox();
        bottomLayout -> addWidget(new QLabel("Numero canali audio:"),2,0);
        bottomLayout -> addWidget(numeroCanali,2,1);
        
        mainLayout -> insertWidget(2,bottom);
    }

    /*bottomFileAudio - prepara la bottom interface con i campi di fileAudio*/
    void AddContenutoView::bottomFileAudio(){
        bottomAudioD();
        QGridLayout* bottomLayout = static_cast<QGridLayout*>(bottom -> layout()); //sono certo sia un QGridLayout

        bottomLayout -> addWidget(new QLabel("Lossy:"),3,0);
        lossy = new QCheckBox();
        bottomLayout -> addWidget(lossy,3,1);

        bottomLayout -> addWidget(new QLabel("Estensione:"),4,0);
        estensione = new QLineEdit();
        bottomLayout -> addWidget(estensione);
    }

    /*bottomVideoD - prepara la bottom interface con i campi di videoD*/
    void AddContenutoView::bottomVideoD(){
        delete bottom;
        bottom = new QWidget();
        QGridLayout* bottomLayout = new QGridLayout(bottom);

        fps = new QSpinBox();
        bottomLayout -> addWidget(new QLabel("FPS:"),0,0);
        bottomLayout -> addWidget(fps,0,1);

        progressivo = new QCheckBox("Progressivo");
        bottomLayout -> addWidget(new QLabel("Scansione:"),1,0);
        bottomLayout -> addWidget(progressivo,1,1);

        risoluzione = new QLineEdit();
        bottomLayout -> addWidget(new QLabel("Risoluzione:"),2,0);
        bottomLayout -> addWidget(risoluzione,2,1);
        
        mainLayout -> insertWidget(2,bottom);
    }

    /*bottomFileVideo - prepara la bottom interface con i campi di fileVideo*/
    void AddContenutoView::bottomFileVideo(){
        bottomVideoD();
        QGridLayout* bottomLayout = static_cast<QGridLayout*>(bottom -> layout());
        estensione = new QLineEdit();
        bottomLayout -> addWidget(new QLabel("Estensione:"),3,0);
        bottomLayout -> addWidget(estensione,3,1);
    }

    /*save - controlla se i campi sono completi, quindi fa istanziare l'oggetto. Errore altrimenti*/
    void AddContenutoView::save(){
        QAbstractButton* b = tipo -> checkedButton();
        if(b){
            if(check() && fd && !fd -> selectedFiles().isEmpty()){ //l'utente ha scritto tutto e di tipo corretto
                if(b->text() == "Audio Digitale" && !freqCamp -> text().isEmpty()) buildAudioD();
                else if(b -> text() == "File Audio" && !freqCamp -> text().isEmpty() && !estensione -> text().isEmpty()) buildFileAudio();
                else if(b -> text() == "Video Digitale" && !risoluzione -> text().isEmpty())  buildVideoD();
                else if(b -> text() == "File Video" && !risoluzione -> text().isEmpty() && !estensione -> text().isEmpty()) buildFileVideo();
            }else{
                error("Uno o più campi incompleti o errati!");
            }
        }else{ 
            error("Non è stato selezionato nessun tipo!");
        }
    }

    /*check - controllo primario sui campi di contenutoMultimediale*/
    bool AddContenutoView::check(){
        bool a;
        anno -> text().toInt(&a);
        return !titolo -> text().isEmpty() && !autori -> text().isEmpty() && !casaProd -> text().isEmpty() && a 
            && !scaffale -> text().isEmpty();
    }

    /*select_image - apre la finestra di QFileDialog nella cartella del progetto per selezionare l'immagine del contenuto
    @see QFileDialog*/
    void AddContenutoView::select_image(){
        fd = new QFileDialog(this);
        fd -> setFileMode(QFileDialog::ExistingFile); //il file deve esistere e deve essere unico
        fd -> setNameFilter(tr("Images (*.png *.xpm *.jpg)")); //il file deve essere di tipo immagine
        fd -> setDirectory(biblioteca::projectPath()); //deve cercarlo dove si trova il progetto
        fd -> exec();
    }

    /*buildAudioD - costruisce l'audioD*/
    void AddContenutoView::buildAudioD(){
        QDir baseDir(biblioteca::projectPath());
        vector<QString> aut;
        for(auto a : autori -> text().split(",")){
            if(a[0]==' '){
                a.remove(0,1);
            }
            aut.push_back(a);
        }
        int sec = (durata -> time().minute() * 60) + (durata -> time().second());
        ptr = new audioD(titolo -> text(), casaProd -> text(), aut, anno -> text().toInt(), sec, baseDir.relativeFilePath(fd -> selectedFiles().first()), 1, freqCamp -> text().toInt(), stereo -> checkState() == Qt::Checked, numeroCanali -> value());
        ptr -> setScaffale(scaffale -> text());
        if(state != 1){
            biblioteca::add(ptr);
            emit(cancel_event());
        }else{
            emit(return_save_event());
        }
    }

    /*buildFileAudio - costruisce il fileAudio*/
    void AddContenutoView::buildFileAudio(){
        QDir baseDir(biblioteca::projectPath());
        vector<QString> aut;
        for(auto a : autori -> text().split(",")){
            if(a[0]==' '){
                a.remove(0,1);
            }
            aut.push_back(a);
        }
        int sec = (durata -> time().minute() * 60) + (durata -> time().second());
        ptr = new fileAudio(titolo -> text(), casaProd -> text(), aut, anno -> text().toInt(), sec, baseDir.relativeFilePath(fd -> selectedFiles().first()), 1, freqCamp -> text().toInt(), stereo -> checkState() == Qt::Checked, numeroCanali -> value(), lossy -> checkState() == Qt::Checked, estensione -> text());
        ptr -> setScaffale(scaffale -> text());
        biblioteca::add(ptr);
        emit(cancel_event());
    }

    /*buildVideoD - costruisce il videoD*/
    void AddContenutoView::buildVideoD(){
        QDir baseDir(biblioteca::projectPath());
        vector<QString> aut;
        for(auto a : autori -> text().split(",")){
            if(a[0]==' '){
                a.remove(0,1);
            }
            aut.push_back(a);
        }
        int sec = (durata -> time().minute() * 60) + (durata -> time().second());
        ptr = new videoD(titolo -> text(), casaProd -> text(), aut, anno -> text().toInt(), sec, baseDir.relativeFilePath(fd -> selectedFiles().first()), 1, fps -> value(), progressivo -> checkState() == Qt::Checked, risoluzione -> text());
        ptr -> setScaffale(scaffale -> text());
        if(state != 2){
            biblioteca::add(ptr);
            emit(cancel_event());
        }else{
            emit(return_save_event());
        }
    }

    /*buildFileVideo - costruisce il fileVideo*/
    void AddContenutoView::buildFileVideo(){
        QDir baseDir(biblioteca::projectPath());
        vector<QString> aut;
        for(auto a : autori -> text().split(",")){
            if(a[0]==' '){
                a.remove(0,1);
            }
            aut.push_back(a);
        }
        int sec = (durata -> time().minute() * 60) + (durata -> time().second());
        ptr = new fileVideo(titolo -> text(), casaProd -> text(), aut, anno -> text().toInt(), sec, baseDir.relativeFilePath(fd -> selectedFiles().first()), 1, fps -> value(), progressivo -> checkState() == Qt::Checked, risoluzione -> text(), estensione -> text());
        ptr -> setScaffale(scaffale -> text());
        biblioteca::add(ptr);
        emit(cancel_event());
    }

    /*getContenuto
    @return il contenutoMultimediale appena costruito*/
    contenutoMultimediale* AddContenutoView::getContenuto() const{
        return ptr;
    }

    /*error - costruisce le messgebox di dialogo
    @param s stringa da mostrare a schermo
    @see QMessageBox*/
    void AddContenutoView::error(QString s){
        QMessageBox e; 
        e.setText(s);
        e.exec();
    }

    /*clearLayout - pulisce il layout rimuovendo ed eliminando i widget
    @param layout layout da pulire*/
    void AddContenutoView::clearLayout(QLayout* layout) {
    if (!layout) return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();   // elimina i widget figli
        }
        if (item->layout()) {
            clearLayout(item->layout()); // ricorsivo
        }
        delete item; // elimina l’item del layout
    }
}
