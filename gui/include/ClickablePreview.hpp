#ifndef CLICKABLE_PREVIEW_HPP
#define CLICKABLE_PREVIEW_HPP

#include <QWidget>
#include <QMouseEvent>
#include <QString>
#include <iostream>

class ClickablePreview: public QWidget{
    Q_OBJECT
public:
    explicit ClickablePreview(QWidget* parent =nullptr);
signals:
    void clicked(int ip);
protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif