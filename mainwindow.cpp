#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "r3deditor_bezier_surface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    viewport(r3d_editor)
{
    ui->setupUi(this);
    ui->viewportLayout->addWidget(&viewport);



    r3deditor::Objects::BezierSurfaceBMatrix B = {
            {{100-250,100-250, 0},   {200-250,100-250, 200}, {300-250,100-250, 200}, {400-250,100-250, 0}},
            {{100-250,200-250, 200}, {200-250,200-250, -200}, {300-250,200-250, 400}, {400-250,200-250, 200}},
            {{100-250,300-250, 200}, {200-250,300-250, 400}, {300-250,300-250, 400}, {400-250,300-250, 200}},
            {{100-250,400-250, 0},   {200-250,400-250, 200}, {300-250,400-250, 200}, {400-250,400-250, 0}},
        };

    r3d_editor.addBezierSurface(B);

    r3deditor::Objects::BezierSurfaceBMatrix B2 = {
            {{100-250,100-250, 0},   {200-250,100-250, 0}, {300-250,100-250, 0}, {400-250,100-250, 0}},
            {{100-250,200-250, 0}, {200-250,200-250, -0}, {300-250,200-250, 0}, {400-250,200-250, 0}},
            {{100-250,300-250, 0}, {200-250,300-250, 0}, {300-250,300-250, 0}, {400-250,300-250, 0}},
            {{100-250,400-250, 0},   {200-250,400-250, 0}, {300-250,400-250, 0}, {400-250,400-250, 0}},
        };

    r3d_editor.addBezierSurface(B2);

    r3d_editor.editObject(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

