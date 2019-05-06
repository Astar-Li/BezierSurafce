#ifndef R3DEDITOR_CAMERA_H
#define R3DEDITOR_CAMERA_H

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
        void setDz(double d);

        //angle
        void setAngleX(double a);
        void setAngleY(double a);
        void setAngleZ(double a);
        double angleX();
        double angleY();
        double angleZ();



        Vertex2D apply(const Vertex3D &v);
    private:
        double    dx, dy, dz;

        double    angle_x, angle_y, angle_z;
        matrix3x3 rx, ry, rz;
    };
}

#endif // R3DEDITOR_CAMERA_H
