#ifndef SEARCH_VIEW_HPP
#define SEARCH_VIEW_HPP

#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QButtonGroup>
#include "../../model/include/query.hpp"

class SearchView: public QGroupBox{
    Q_OBJECT
private:
    QButtonGroup* radioGroup;
    QLineEdit* src;
    QRadioButton* all;
    QRadioButton* isAudioD;
    QRadioButton* isVideoD;
    QRadioButton* isFileA;
    QRadioButton* isFileV;
    QRadioButton* isCD;
    QRadioButton* isDVD;
    QCheckBox* searchTitle;
    QCheckBox* searchArtist;
    QCheckBox* searchYear;
    QPushButton* go;
public:
    explicit SearchView(QWidget* parent =nullptr);
signals:
    void search_event(query q);
public slots:
    void search();
};

#endif