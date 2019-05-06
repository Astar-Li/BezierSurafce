#include "r3deditor_mouse_control.h"

#include <QDebug>

using namespace r3deditor;

MouseControl::MouseControl(Camera &camera) :
    camera(camera)
{
}

void MouseControl::sendEvent(QMouseEvent *event)
{
    //rotate
    static double angle_x, angle_y;
    static double x1, y1;
    static bool   left_button_pressed = false;
    if ((event->type() == QEvent::MouseButtonPress) && (event->button() == Qt::LeftButton))
    {
        left_button_pressed = true;
        angle_x = camera.angleX();
        angle_y = camera.angleY();
        x1      = event->pos().rx();
        y1      = event->pos().ry();
    }
    if ((event->type() == QEvent::MouseMove)&&(left_button_pressed))
    {
        double x2 = event->pos().rx();
        double y2 = event->pos().ry();
        camera.setAngleX(angle_x - (y2 - y1)/100);
        camera.setAngleY(angle_y + (x2 - x1)/100);
    }
    if ((event->type() == QEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton))
    {
        left_button_pressed = false;
    }
}
