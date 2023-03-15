#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include "playerwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   QPushButton *btnPlay = new QPushButton(this);
   btnPlay->setText("Play");
   btnPlay->setGeometry(30, 30, 100, 40);
   connect(btnPlay, &QPushButton::clicked, [=](){
       PlayerWidget *w = new PlayerWidget();
       w->show();
   });
}

MainWindow::~MainWindow()
{
    delete ui;
}


