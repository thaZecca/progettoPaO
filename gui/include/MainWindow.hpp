#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include "../../fileManager/include/biblioteca.hpp"
#include "../../visitor/include/PreviewVisitor.hpp"
#include "ItemView.hpp"

class MainWindow: public QMainWindow{
    Q_OBJECT
private:
    QWidget* prova;
public:
    explicit MainWindow(QWidget *parent = nullptr);
};

#endif