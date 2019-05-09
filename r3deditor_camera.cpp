#include <cmath>

#include "r3deditor_camera.h"

using namespace r3deditor;

Camera::Camera() :
    quaternion_rx(1,0,0,0),
    quaternion_ry(1,0,0,0),
    quaternion_rz(1,0,0,0),
    quaternion_rxyz(1,0,0,0)
{
    angle.x = 0; angle.y = 0; angle.z = 0;
    d.x = 0; d.y = 0; d.z = 0;
}

void Camera::setDx(double d)
{
    this->d.x = d;
    notifyObservers();
}

void Camera::setDy(double d)
{
    this->d.y = d;
    notifyObservers();
}

void Camera::setDz(double d)
{
    this->d.z = d;
    notifyObservers();
}

void Camera::setAngleX(double a)
{
    angle.x = a;
    quaternion_rx = QQuaternion(cos(a/2), sin(a/2)*QVector3D(1,0,0));
    quaternion_rxyz = quaternion_rx * quaternion_ry * quaternion_rz;
    notifyObservers();
}

void Camera::setAngleY(double a)
{
    angle.y = a;
    quaternion_ry = QQuaternion(cos(a/2), sin(a/2)*QVector3D(0,1,0));
    quaternion_rxyz = quaternion_rx * quaternion_ry * quaternion_rz;
    notifyObservers();
}

void Camera::setAngleZ(double a)
{
    angle.z = a;
    quaternion_rz = QQuaternion(cos(a/2), sin(a/2)*QVector3D(0,0,1));
    quaternion_rxyz = quaternion_rx * quaternion_ry * quaternion_rz;
    notifyObservers();
}


double Camera::angleX()
{
    return angle.x;
}

double Camera::angleY()
{
    return angle.y;
}

double Camera::angleZ()
{
    return angle.z;
}

Vertex2D Camera::apply(const Vertex3D &v)
{    
    QVector3D qvres3d = quaternion_rxyz.rotatedVector(QVector3D(v.x, v.y, v.z));
    return {qvres3d.x() + d.x, qvres3d.y() + d.y};
}


Vertex2D Camera::applyWithoutD(const Vertex3D &v)
{
    QVector3D qvres3d = quaternion_rxyz.rotatedVector(QVector3D(v.x, v.y, v.z));
    return {qvres3d.x(), qvres3d.y()};
}
