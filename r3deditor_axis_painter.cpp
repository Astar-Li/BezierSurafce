#include "r3deditor_axis_painter.h"

#include <QPainter>

using namespace r3deditor;

AxisPainter::AxisPainter(QImage &image_bufer, Camera &camera) :
    image_bufer(image_bufer),
    camera(camera)
{

}

void AxisPainter::perform()
{
    QPainter qpainter;
    qpainter.begin(&image_bufer);

    Vertex2D o2d = camera.apply({0,0,0});

    //x axis
    qpainter.setPen(Qt::red);
    Vertex2D x_axis2d = camera.apply({100,0,0});
    qpainter.drawLine(o2d.x, o2d.y, x_axis2d.x, x_axis2d.y);

    //y axis
    qpainter.setPen(Qt::green);
    Vertex2D y_axis2d = camera.apply({0,100,0});
    qpainter.drawLine(o2d.x, o2d.y, y_axis2d.x, y_axis2d.y);

    //z axis
    qpainter.setPen(Qt::blue);
    Vertex2D z_axis2d = camera.apply({0,0,100});
    qpainter.drawLine(o2d.x, o2d.y, z_axis2d.x, z_axis2d.y);


    qpainter.end();
}
