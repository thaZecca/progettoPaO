#ifndef STAT_VIEW_HPP
#define STAT_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../model/include/audioD.hpp"
#include "../../model/include/cd.hpp"
#include "../../model/include/dvd.hpp"
#include "../../model/include/fileAudio.hpp"
#include "../../model/include/fileVideo.hpp"
#include "../../model/include/videoD.hpp"

class StatView: public QGroupBox{
    Q_OBJECT
private:
    QGridLayout* mainLayout;
    QLabel* tot;
    QLabel* totC;
    QLabel* totAD;
    QLabel* totVD;
    QLabel* totFA;
    QLabel* totD;
    QLabel* totFV;
    void prepare();
public:
    explicit StatView(QWidget* parent =nullptr);
    void repaint();
};

#endif