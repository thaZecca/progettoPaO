#ifndef ADD_CONTENUTO_HPP
#define ADD_CONTENUTO_HPP

#include <QWidget>
#include <QDir>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
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

class AddContenutoView: public QWidget{
    Q_OBJECT
private:
    contenutoMultimediale* ptr;
    int state;
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
    QButtonGroup* tipo;
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
    void buildAudioD();
    void buildFileAudio();
    void buildVideoD();
    void buildFileVideo();
    void bottomAudioD();
    void bottomFileAudio();
    void bottomVideoD();
    void bottomFileVideo();
    void error(QString);
public:
    explicit AddContenutoView(int s, QWidget* parent =nullptr);
    contenutoMultimediale* getContenuto() const;
    static void clearLayout(QLayout*);
public slots:
    void type_event(QAbstractButton*);
    void save();
    void select_image();
signals:
    void cancel_event();
    void return_save_event();
};

#endif