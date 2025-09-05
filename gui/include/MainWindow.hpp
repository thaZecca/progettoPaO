#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"
#include "ItemView.hpp"
#include "StatView.hpp"
#include "MainButtonView.hpp"
#include "SearchView.hpp"

class MainWindow: public QWidget{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QWidget* right;
    ItemView* previews;
    StatView* statistics;
    SearchView* search;
    MainButtonView* buttons;
    void prepareMainRightWindow();
    void prepareFullPreview();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void prepareMainWindow();
signals:
    void reload_preview_event();
public slots:
    void save();
    void reload();
    void show_full_preview(int ip);
};

#endif