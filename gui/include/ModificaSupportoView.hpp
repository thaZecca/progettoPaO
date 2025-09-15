#ifndef MODIFICA_SUPPORTO_VIEW_HPP
#define MODIFICA_SUPPORTO_VIEW_HPP

#include "../../fileManager/include/biblioteca.hpp"
#include "../../model/include/supportoMultimediale.hpp"
#include "../../model/include/audioD.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"
#include "AddContenutoView.hpp"
#include "AddSupportoView.hpp"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSpinBox>

class ModificaSupportoView: public QWidget{
    Q_OBJECT
private:
    supportoMultimediale* ptr;
    QVBoxLayout* mainLayout;
    QLabel* ti;
    QLabel* s;
    QLabel* trc;
    QLabel* di;
    QLineEdit* titolo;
    QLineEdit* scaffale;
    QSpinBox* diametro;
    QLabel* avvisoRimozione;
    QPushButton* rimozione;
    QPushButton* add;
    QPushButton* cancel;
    QPushButton* save;
    QWidget* areaTracce;
    QVBoxLayout* layoutScrollable;
    QScrollArea* scrollTracce;
    vector<contenutoMultimediale*> tracce;
    AddContenutoView* aggiuntaTraccia;
    bool rimozione_attiva;
    void prepare();
    void prepareScrollable();
public:
    explicit ModificaSupportoView(supportoMultimediale*, QWidget* =nullptr);
signals:
    void cancel_event();
public slots:
    void addTracce();
    void set_rimozione();
    void cancelTraccia();
    void salvaTraccia();
    void click_preview(int ip);
    void salva();
};

#endif