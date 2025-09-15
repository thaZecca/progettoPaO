#ifndef MODIFICA_CONTENUTO_HPP
#define MODIFICA_CONTENUTO_HPP

#include <QWidget>
#include <QDir>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPixmap>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../model/include/contenutoMultimediale.hpp"

class ModificaContenutoView: public QWidget{
    Q_OBJECT
private:
    contenutoMultimediale* ptr;
    QWidget* bottom;
    QVBoxLayout* mainLayout;
    QFileDialog* fd;
    QPushButton* picSelect;
    QLineEdit* titolo;
    QLineEdit* autori;
    QLineEdit* casaProd;
    QLineEdit* anno;
    QDateTimeEdit* durata;
    QLineEdit* scaffale;
    
    QPushButton* cancella;
    QPushButton* salva;
    //audioD
    QLineEdit* freqCamp;
    QCheckBox* stereo;
    QSpinBox* numeroCanali;
    //fileAudio
    QCheckBox* lossy;
    //fileAudio/fileVideo
    QLineEdit* estensione;
    //videoD
    QSpinBox* fps;
    QCheckBox* progressivo;
    QLineEdit* risoluzione;
    bool check();
    void bottomAudioD();
    void bottomFileAudio();
    void bottomVideoD();
    void bottomFileVideo();
    void modifyAudioD();
    void modifyFileAudio();
    void modifyVideoD();
    void modifyFileVideo();
public:
    explicit ModificaContenutoView(contenutoMultimediale*, QWidget* =nullptr);
signals:
    void cancel_event();
public slots:
    void save();
    void choose_picture();
};

#endif