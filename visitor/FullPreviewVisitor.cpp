#include "include/FullPreviewVisitor.hpp"

/*prepare - prepare il widget di fullpreview da ritornare*/
void FullPreviewVisitor::prepare(){
    fullPreview = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(fullPreview);
    mainLayout -> addWidget(pic);
    mainLayout -> addWidget(titolo);

    if(tracce != nullptr){
        mainLayout -> addWidget(tracce);
    }else{
        mainLayout -> addWidget(artisti);

        QWidget* prodAnno = new QWidget(fullPreview);
        QHBoxLayout* prodAnnoLayout = new QHBoxLayout(prodAnno);
        prodAnnoLayout -> addWidget(casaProd);
        prodAnnoLayout -> addWidget(annoPubb);
        mainLayout -> addWidget(prodAnno);
    }
    QWidget* logoProprieta = new QWidget(fullPreview);
    QHBoxLayout* logoProprietaLayout = new QHBoxLayout(logoProprieta);
    logoProprietaLayout -> addWidget(logo);
    logoProprietaLayout -> addWidget(proprieta);
    mainLayout -> addWidget(logoProprieta);
    mainLayout -> addWidget(action);
}

/*visit - design pattern per visitare l'audioD
@param a audioD da visitare*/
void FullPreviewVisitor::visit(audioD* a){
    tracce = nullptr;
    pic = new QLabel();
    QPixmap picture(biblioteca::projectPath().filePath("src/placeholder.png"));
    pic -> setPixmap(picture.scaled(200,100, Qt::KeepAspectRatio));

    titolo = new QLabel(a -> getTitolo());
    
    QString art("");
    vector<QString> autori = a -> getAutori();
    for(auto it = autori.begin(); it != autori.end(); it++){
        art += *it + "\n";
    }
    artisti = new QLabel(art);

    casaProd = new QLabel(a -> getCasaProduttrice());

    annoPubb = new QLabel(QString::number(a -> getAnnoDiPubblicazione()));

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/audioD.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(QString::number(a -> getFrequenzaCampionamento())+"Hz");

    if(a -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*visit- design pattern per visitare il fileAudio
@param f fileAudio da visitare*/
void FullPreviewVisitor::visit(fileAudio* f){
    tracce = nullptr;
    pic = new QLabel();
    QPixmap picture(biblioteca::projectPath().filePath("src/placeholder.png"));
    pic -> setPixmap(picture.scaled(200,100, Qt::KeepAspectRatio));

    titolo = new QLabel(f -> getTitolo());
    
    QString art("");
    vector<QString> autori = f -> getAutori();
    for(auto it = autori.begin(); it != autori.end(); it++){
        art += *it + "\n";
    }
    artisti = new QLabel(art);

    casaProd = new QLabel(f -> getCasaProduttrice());

    annoPubb = new QLabel(QString::number(f -> getAnnoDiPubblicazione()));

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/fileAudio.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(f -> getEstensione());

    if(f -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*visit - degisn pattern per visitare il cd
@param c cd da visitare*/
void FullPreviewVisitor::visit(cd* c){
    pic = new QLabel();
    QPixmap image(200,200);
    image.fill(Qt::transparent);
    QPainter* painter = new QPainter(&image);
    painter -> drawPixmap(0,0,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(0,100,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(100,0,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(100,100,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> end();

    pic -> setPixmap(image);

    titolo = new QLabel(c -> getTitolo());
    
    tracce = new QScrollArea();
    QWidget* mainWidgetScroll = new QWidget();
    QVBoxLayout* mainWidgetLayout = new QVBoxLayout(mainWidgetScroll);
    QWidget* littlePreview;
    QHBoxLayout* littlePreviewLayout;

    vector<contenutoMultimediale*> cont = c -> getTracce();
    for(auto it = cont.begin(); it != cont.end(); it++){
        QLabel* t = new QLabel((*it) -> getTitolo());
        QLabel* a = new QLabel();
        QString s("");

        vector<QString> autori = (*it) -> getAutori();
        for(auto& aut : autori){
            s += aut + " ";
        }
        a -> setText(s);
        littlePreview = new QWidget();
        littlePreviewLayout = new QHBoxLayout(littlePreview);
        littlePreviewLayout -> addWidget(t);
        littlePreviewLayout -> addWidget(a);
        littlePreviewLayout -> addStretch();
        mainWidgetLayout -> addWidget(littlePreview);
    }
    mainWidgetLayout -> addStretch();
    tracce -> setWidget(mainWidgetScroll);

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/cd.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(QString::number(c -> getDiametro())+"cm");

    if(c -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*visit - design pattern per visitare il videoD
@param v videoD da visitare*/
void FullPreviewVisitor::visit(videoD* v){
    tracce = nullptr;
    pic = new QLabel();
    QPixmap picture(biblioteca::projectPath().filePath("src/placeholder.png"));
    pic -> setPixmap(picture.scaled(200,100, Qt::KeepAspectRatio));

    titolo = new QLabel(v -> getTitolo());
    
    QString art("");
    vector<QString> autori = v -> getAutori();
    for(auto it = autori.begin(); it != autori.end(); it++){
        art += *it + "\n";
    }
    artisti = new QLabel(art);

    casaProd = new QLabel(v -> getCasaProduttrice());

    annoPubb = new QLabel(QString::number(v -> getAnnoDiPubblicazione()));

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/videoD.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(v -> getRisoluzione()+(v->isProgressivo()?"p":"i"));

    if(v -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*visit - design pattern per visitare il fileVideo
@param f fileVideo da visitare*/
void FullPreviewVisitor::visit(fileVideo* f){
    tracce = nullptr;
    pic = new QLabel();
    QPixmap picture(biblioteca::projectPath().filePath("src/placeholder.png"));
    pic -> setPixmap(picture.scaled(200,100, Qt::KeepAspectRatio));

    titolo = new QLabel(f -> getTitolo());
    
    QString art("");
    vector<QString> autori = f -> getAutori();
    for(auto it = autori.begin(); it != autori.end(); it++){
        art += *it + "\n";
    }
    artisti = new QLabel(art);

    casaProd = new QLabel(f -> getCasaProduttrice());

    annoPubb = new QLabel(QString::number(f -> getAnnoDiPubblicazione()));

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/fileVideo.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(f -> getEstensione());

    if(f -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*visit - design pattern per visitare dvd
@param v dvd da visitare*/
void FullPreviewVisitor::visit(dvd* v){
    pic = new QLabel();
    QPixmap image(200,200);
    image.fill(Qt::transparent);
    QPainter* painter = new QPainter(&image);
    painter -> drawPixmap(0,0,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(0,100,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(100,0,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> drawPixmap(100,100,100,100, QPixmap(biblioteca::projectPath().filePath("src/placeholder.png")));
    painter -> end();

    pic -> setPixmap(image);

    titolo = new QLabel(v -> getTitolo());

    tracce = new QScrollArea();
    QWidget* mainWidgetScroll = new QWidget();
    QVBoxLayout* mainWidgetLayout = new QVBoxLayout(mainWidgetScroll);
    QWidget* littlePreview;
    QHBoxLayout* littlePreviewLayout;
    vector<contenutoMultimediale*> cont = v -> getTracce();
    for(auto it = cont.begin(); it != cont.end(); it++){
        QLabel* t = new QLabel((*it) -> getTitolo());
        QLabel* a = new QLabel();
        QString s("");
        vector<QString> autori = (*it) -> getAutori();
        for(auto& aut : autori){
            s += aut + " ";
        }
        a -> setText(s);
        littlePreview = new QWidget();
        littlePreviewLayout = new QHBoxLayout(littlePreview);
        littlePreviewLayout -> addWidget(t);
        littlePreviewLayout -> addWidget(a);
        littlePreviewLayout -> addStretch();
        mainWidgetLayout -> addWidget(littlePreview);
    }
    mainWidgetLayout -> addStretch();
    tracce -> setWidget(mainWidgetScroll);

    logo = new QLabel();
    QPixmap audioLogo(biblioteca::projectPath().filePath("src/dvd.png"));
    logo -> setPixmap(audioLogo.scaled(100,50, Qt::KeepAspectRatio));

    proprieta = new QLabel(QString::number(v -> getDiametro())+"cm");

    if(v -> isInPrestito()) action = new QPushButton("Rientra");
    else action = new QPushButton("Presta");
}

/*getFullPreview
@return la fullpreview dell'oggetto*/
QWidget* FullPreviewVisitor::getFullPreview(){
    prepare();
    return fullPreview;
}