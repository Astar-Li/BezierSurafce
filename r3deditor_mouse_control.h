#ifndef R3DEDITOR_MOUSE_CONTROL_H
#define R3DEDITOR_MOUSE_CONTROL_H

#include <QMouseEvent>

#include "r3deditor_camera.h"

namespace r3deditor
{
    class MouseControl
    {
    public:
        MouseControl(Camera &camera);
        void sendEvent(QMouseEvent *event);
    private:
        Camera &camera;
    };
}
#endif // R3DEDITOR_MOUSE_CONTROL_H
