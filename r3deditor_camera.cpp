#include <cmath>


#include "r3deditor_camera.h"

using namespace r3deditor;

Camera::Camera()
{
    setAngleX(0);
    setAngleY(0);
    setAngleZ(0);
    setDx(0);
    setDy(0);
    setDz(0);
}

double Camera::angleX()
{
    return angle_x;
}

double Camera::angleY()
{
    return angle_y;
}

double Camera::angleZ()
{
    return angle_z;
}

void Camera::setDx(double d)
{
    dx = d;
    notifyObservers();
}

void Camera::setDy(double d)
{
    dy = d;
    notifyObservers();
}

void Camera::setDz(double d)
{
    dz = d;
    notifyObservers();
}

void Camera::setAngleX(double a)
{
    angle_x = a;

    rx[0][0] = 1; rx[0][1] = 0;      rx[0][2] = 0;
    rx[1][0] = 0; rx[1][1] = cos(a); rx[1][2] = -sin(a);
    rx[2][0] = 0; rx[2][1] = sin(a); rx[2][2] = cos(a);

    notifyObservers();
}

void Camera::setAngleY(double a)
{
    angle_y = a;

    ry[0][0] = cos(a);  ry[0][1] = 0; ry[0][2] = sin(a);
    ry[1][0] = 0;       ry[1][1] = 1; ry[1][2] = 0;
    ry[2][0] = -sin(a); ry[2][1] = 0; ry[2][2] = cos(a);

    notifyObservers();
}

void Camera::setAngleZ(double a)
{
    angle_z = a;

    rz[0][0] = cos(a); rz[0][1] = -sin(a); rz[0][2] = 0;
    rz[1][0] = sin(a); rz[1][1] = cos(a);  rz[1][2] = 0;
    rz[2][0] = 0;      rz[2][1] = 0;       rz[2][2] = 1;

    notifyObservers();
}

Vertex2D Camera::apply(const Vertex3D &v)
{
    Vertex3D vres3d;
    Vertex2D vres2d;

    //rotate x
    vres3d.x = rx[0][0] * v.x + rx[0][1] * v.y + rx[0][2] * v.z;
    vres3d.y = rx[1][0] * v.x + rx[1][1] * v.y + rx[1][2] * v.z;
    vres3d.z = rx[2][0] * v.x + rx[2][1] * v.y + rx[2][2] * v.z;
    //rotate y
    vres3d.x = ry[0][0] * vres3d.x + ry[0][1] * vres3d.y + ry[0][2] * vres3d.z;
    vres3d.y = ry[1][0] * vres3d.x + ry[1][1] * vres3d.y + ry[1][2] * vres3d.z;
    vres3d.z = ry[2][0] * vres3d.x + ry[2][1] * vres3d.y + ry[2][2] * vres3d.z;
    //rotate z
    vres3d.x = rz[0][0] * vres3d.x + rz[0][1] * vres3d.y + rz[0][2] * vres3d.z;
    vres3d.y = rz[1][0] * vres3d.x + rz[1][1] * vres3d.y + rz[1][2] * vres3d.z;
    vres3d.z = rz[2][0] * vres3d.x + rz[2][1] * vres3d.y + rz[2][2] * vres3d.z;

    vres2d.x = vres3d.x + dx;
    vres2d.y = vres3d.y + dy;
    return vres2d;
}
