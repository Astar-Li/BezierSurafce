#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    viewport(r3d_editor)
{
    ui->setupUi(this);

    ui->viewportLayout->addWidget(&viewport);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    viewport.handleNotification();
}
