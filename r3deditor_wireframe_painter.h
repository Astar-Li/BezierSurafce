#ifndef R3DEDITOR_PAINTERS_H
#define R3DEDITOR_PAINTERS_H

#include <QImage>

#include "r3deditor_3d_types.h"
#include "r3deditor_camera.h"

namespace r3deditor
{
    class WireframePainter
    {
    public:
        WireframePainter(Scene &scene, QImage &image_bufer, Camera &camera);
        void perform();
    private:
        Scene   &scene;
        QImage  &image_bufer;
        Camera  &camera;
    };
}


#endif // R3DEDITOR_PAINTERS_H
