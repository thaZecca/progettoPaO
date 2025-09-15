#ifndef ADD_SUPPORTO_VIEW_HPP
#define ADD_SUPPORTO_VIEW_HPP

#include "../../fileManager/include/biblioteca.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "../../model/include/audioD.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"
#include "AddContenutoView.hpp"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSpinBox>

class AddSupportoView: public QWidget{
    Q_OBJECT
private:
    AddContenutoView* aC;
    QVBoxLayout* mainLayout;
    QLabel* ti;
    QLabel* s;
    QLabel* trc;
    QLabel* di;
    QLineEdit* titolo;
    QLineEdit* scaffale;
    QSpinBox* diametro;
    QRadioButton* c;
    QRadioButton* d;
    QButtonGroup* tipo;
    QPushButton* add;
    QPushButton* cancel;
    QPushButton* save;
    QWidget* areaTracce;
    vector<contenutoMultimediale*> tracce;
    QVBoxLayout* layoutScrollable;
    QScrollArea* scrollTracce;
    void prepare();
    void prepareScrollable();
    void error(QString);
public:
    explicit AddSupportoView(QWidget* parent =nullptr);
    static void saveLayout(QLayout*);
signals:
    void cancel_event();
public slots:
    void addTracce();
    void addTracce_cancel();
    void addTracce_save();
    void cambioTipo();
    void salva();
};

#endif