#include "include/AddContenutoView.hpp"

/*Costruttore parametrico di AddContenutoView
@param parent*/
AddContenutoView::AddContenutoView(QWidget* parent): 
    QWidget(parent), bottom(nullptr), fd(nullptr), picSelect(nullptr), titolo(nullptr), autori(nullptr), 
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
        delete bottom;
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

    void AddContenutoView::save(){
        QAbstractButton* b = tipo -> checkedButton();
        if(b){
            if(check()){
                if(b->text() == "Audio Digitale") qDebug() << "ok";
            }else{
                QMessageBox error;
                error.setText("Uno o più campi incompleti o errati!");
                error.exec();
            }
        }else{
            QMessageBox error; 
            error.setText("Non è stato selezionato nessun tipo!");
            error.exec();
        }
    }

    bool AddContenutoView::check(){
        bool a;
        anno -> text().toInt(&a);
        return !titolo -> text().isEmpty() && !autori -> text().isEmpty() && !casaProd -> text().isEmpty() && a 
            && !scaffale -> text().isEmpty();
    }

