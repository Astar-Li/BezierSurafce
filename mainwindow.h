#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "imagewidget.h"
#include "r3deditor.h"
#include "r3deditor_viewport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    r3deditor::R3DEditor  r3d_editor;
    R3DEditorViewport     viewport;
    Ui::MainWindow        *ui;
};

#endif // MAINWINDOW_H
