#ifndef R3DEDITOR_CAMERA_H
#define R3DEDITOR_CAMERA_H

#include <QQuaternion>

#include "observer.h"
#include "r3deditor_3d_types.h"

namespace r3deditor
{
    class Camera : public Observable
    {
    public:
        Camera();
        //dx,dy
        void setDx(double d);
        void setDy(double d);
        double dx();
        double dy();

        //angle
        void setAngleX(double a);
        void setAngleY(double a);
        void setAngleZ(double a);
        double angleX();
        double angleY();
        double angleZ();

        Vertex2D    apply(const Vertex3D &v);
        QQuaternion quaternion();
    private:
        Vertex2D    d;
        Vertex3D    angle;
        QQuaternion quaternion_rx, quaternion_ry, quaternion_rz;
        QQuaternion quaternion_rxyz;
    };
}

#endif // R3DEDITOR_CAMERA_H
