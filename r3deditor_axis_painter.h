#ifndef R3DEDITOR_AXIS_PAINTER_H
#define R3DEDITOR_AXIS_PAINTER_H

#include "r3deditor_camera.h"

namespace r3deditor
{
    class AxisPainter
    {
    public:
        AxisPainter(QImage &image_bufer, Camera &camera);
        void perform();
    private:
        QImage  &image_bufer;
        Camera  &camera;
    };
}

#endif // R3DEDITOR_AXIS_PAINTER_H
