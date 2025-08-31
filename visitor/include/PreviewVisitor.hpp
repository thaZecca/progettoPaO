#ifndef ITEM_VIEW_VISITOR_HPP
#define ITEM_VIEW_VISITOR_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "visitorCMultimediale.hpp"
#include "../../fileManager/include/biblioteca.hpp"

class PreviewVisitor: public QObject, public visitorCMultimediale{
    Q_OBJECT
private:
    QWidget* preview; 
    QLabel* pic;
    QLabel* titolo;
    QLabel* artisti;
    QLabel* anno;
    QLabel* logo;
    QLabel* qualita;
    void prepare();
public:
    explicit PreviewVisitor(QObject* parent =nullptr);
    virtual void visit(audioD*) override;
    virtual void visit(videoD*) override;
    virtual void visit(fileAudio*) override;
    virtual void visit(fileVideo*) override;
    virtual void visit(cd*) override;
    virtual void visit(dvd*) override;
    QWidget* getPreview();
}

#endif