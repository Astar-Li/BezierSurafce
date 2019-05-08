#include <cmath>

#include <QQuaternion>
#include <QDebug>

#include "r3deditor_mouse_control.h"

using namespace r3deditor;

MouseControl::MouseControl(Camera &camera) :
    camera(camera)
{
}

void MouseControl::sendEvent(QMouseEvent *event)
{
    //rotate
    static double angle_x1, angle_z1;
    static double x1, y1;
    static bool   left_button_pressed = false;
    if ((event->type() == QEvent::MouseButtonPress) && (event->button() == Qt::LeftButton))
    {
        left_button_pressed = true;
        x1      = event->pos().rx();
        y1      = event->pos().ry();
        angle_x1 = camera.angleX();
        angle_z1 = camera.angleZ();
    }
    if ((event->type() == QEvent::MouseMove)&&(left_button_pressed))
    {
        double x2 = event->pos().rx();
        double y2 = event->pos().ry();

        double dx = x2-x1;
        double dy = y2-y1;
        double angle_x2 = -dy*ROTATE_SESITIVITY;
        double angle_z2 = -dx*ROTATE_SESITIVITY;

        //abs(x rotate) < PI/2
        double angle_resx = angle_x1 + angle_x2;
        //double angle_resz = angle_z1 + angle_z2;
        if (angle_resx > MATH_PI/2)
            angle_resx = MATH_PI/2;
        if (angle_resx < -MATH_PI/2)
            angle_resx = -MATH_PI/2;

        camera.setAngleX(angle_resx);
        camera.setAngleZ(angle_z1 + angle_z2);
    }
    if ((event->type() == QEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton))
    {
        left_button_pressed = false;
    }
}

