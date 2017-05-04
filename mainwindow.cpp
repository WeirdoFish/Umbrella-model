#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myqopenglwidget.h"
MainWindow::MainWindow(QWidget *parent) :     QMainWindow(parent),     ui(new Ui::MainWindow){
    ui->setupUi(this);
//    QObject::connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), ui->MyOpenGLWidget, SLOT(changeType(QString)));
}

MainWindow::~MainWindow(){
    delete ui;
}
