#ifndef MAIN_BUTTON_VIEW_HPP
#define MAIN_BUTTON_VIEW_HPP

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class MainButtonView: public QWidget{
    Q_OBJECT
private:
    QPushButton* add;
    QPushButton* remove;
    QPushButton* save;
    QPushButton* reload;
public:
    explicit MainButtonView(QWidget* parent =nullptr);
};

#endif