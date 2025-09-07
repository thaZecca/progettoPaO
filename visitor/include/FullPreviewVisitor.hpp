#ifndef FULL_PREVIEW_VISITOR_HPP
#define FULL_PREVIEW_VISITOR_HPP

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QString>
#include "visitorCMultimediale.hpp"
#include "../../fileManager/include/biblioteca.hpp"

class FullPreviewVisitor: public visitorCMultimediale{
private:
    QWidget* fullPreview;
    QLabel* pic;
    QLabel* titolo;
    QLabel* artisti;
    QLabel* casaProd;
    QLabel* annoPubb;
    QLabel* logo;
    QLabel* proprieta;
    QPushButton* action;
    QScrollArea* tracce;
    void prepare();
public:
    virtual void visit(audioD*) override;
    virtual void visit(fileAudio*) override;
    virtual void visit(cd*) override;
    virtual void visit(videoD*) override;
    virtual void visit(fileVideo*) override;
    virtual void visit(dvd*) override;
    QWidget* getFullPreview();
};

#endif