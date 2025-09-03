#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
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
};

#endif