#include "include/PreviewVisitor.hpp"

/*Costruttore parametrico
@param parent parent di this*/
PreviewVisitor::PreviewVisitor(QObject* parent): QObject(parent) {}

/*prepare - prepara la preview*/
void PreviewVisitor::prepare(){
    if(preview) preview = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout(preview);
    mainLayout -> setAlignment(Qt::AlignLeft | Qt::AlignTop);

    mainLayout -> addWidget(pic);

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout -> addWidget(titolo);
    infoLayout -> addWidget(artisti);
    infoLayout -> addWidget(anno);

    mainLayout -> addLayout(infoLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout -> addWidget(logo);
    rightLayout -> addWidget(qualita);

    mainLayout -> addLayout(rightLayout);
}

/*visit - design pattern per visitare l'audioD
@param a oggetto audioD da visitare*/
void PreviewVisitor::visit(audioD* a){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(a -> getTitolo());
    artisti = new QLabel();
    QString art("");
    for(auto it = a->getAutori().begin(); it != a->getAutori().end(); it++){
        art += *it;
    }
    artisti -> setText(art);
    anno = new QLabel();
    anno -> setText(a -> getAnnoDiPubblicazione());
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(a -> getFrequenzaCampionamento());
}

/*visit - design pattern per visitare il videoD
@param v oggetto videoD da visitare*/
void PreviewVisitor::visit(videoD* v){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(v -> getTitolo());
    artisti = new QLabel();
    QString art("");
    for(auto it = v->getAutori().begin(); it != v->getAutori().end(); it++){
        art += *it;
    }
    artisti -> setText(art);
    anno = new QLabel();
    anno -> setText(v -> getAnnoDiPubblicazione());
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(v -> getRisoluzione());
}

/*visit - design pattern per visitare il fileAudio
@param f oggetto fileAudio da visitare*/
void PreviewVisitor::visit(fileAudio* f){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(f -> getTitolo());
    artisti = new QLabel();
    QString art("");
    for(auto it = f->getAutori().begin(); it != f->getAutori().end(); it++){
        art += *it;
    }
    artisti -> setText(art);
    anno = new QLabel();
    anno -> setText(f -> getAnnoDiPubblicazione());
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(f -> getEstensione());
}

/*visit - design pattern per visitare il fileVideo
@param f oggetto fileVideo da visitare*/
void PreviewVisitor::visit(fileVideo* f){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(f -> getTitolo());
    artisti = new QLabel();
    QString art("");
    for(auto it = f->getAutori().begin(); it != f->getAutori().end(); it++){
        art += *it;
    }
    artisti -> setText(art);
    anno = new QLabel();
    anno -> setText(f -> getAnnoDiPubblicazione());
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(f -> getEstensione());
}

/*visit - design pattern per visitare il CD
@param c oggetto CD da visitare*/
void PreviewVisitor::visit(cd* c){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(c -> getTitolo());
    artisti = new QLabel();
    artisti -> setText("");
    anno = new QLabel();
    anno -> setText("");
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(c -> getDiametro());
}

/*visit - design pattern per visitare il DVD
@param d oggetto DVD da visitare*/
void PreviewVisitor::visit(dvd* d){
    pic = new QLabel();
    QPixmap image(biblioteca::projectPath().filePath("/src/placeholder.png"));
    pic -> setPixmap(image);
    titolo = new QLabel()
    titolo -> setText(d -> getTitolo());
    artisti = new QLabel();
    artisti -> setText("");
    anno = new QLabel();
    anno -> setText("");
    logo = new QLabel();
    QPixmap logo(biblioteca::projectPath().filePath("/src/placeholder.png"));
    logo -> setPixmap(logo);
    qualita = new QLabel();
    qualita -> setText(d -> getDiametro());
}

/*getPreview
@return la preview del contenutoMultimediale o del supportoMultimediale*/
QWidget* PreviewVisitor::getPreview(){
    prepare();
    return preview;
}
