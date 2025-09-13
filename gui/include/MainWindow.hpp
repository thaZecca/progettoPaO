#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"
#include "ItemView.hpp"
#include "StatView.hpp"
#include "MainButtonView.hpp"
#include "SearchView.hpp"
#include "FullPreview.hpp"
#include "AddObjectView.hpp"

class MainWindow: public QWidget{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QWidget* right;
    ItemView* previews;
    StatView* statistics;
    SearchView* search;
    MainButtonView* buttons;
    FullPreview* fullprev;
    AddObjectView* addobject;
    QLabel* status;
    bool remove_activated;
    void prepareMainRightWindow();
    void show_full_preview(int);
    void remove(int);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void prepareMainWindow();
signals:
    void reload_preview_event();
public slots:
    void save();
    void reload();
    void dispatcher(int);
    void back();
    void add_object();
    void add_back();
    void set_remove();
};

#endif