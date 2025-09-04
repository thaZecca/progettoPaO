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
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:
    void reload_preview_event();
public slots:
    void save();
    void reload();
};

#endif