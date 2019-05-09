#ifndef R3DEDITOR_MOUSE_CONTROL_H
#define R3DEDITOR_MOUSE_CONTROL_H

#include <QMouseEvent>

#include "r3deditor_camera.h"
#include "r3deditor_object.h"

namespace r3deditor
{
    class MouseControl
    {
    public:
        MouseControl(Camera &camera, PObjectEditor &p_object_editor);
        void mouseEvent(QMouseEvent *event);
    private:
        Camera         &camera;
        PObjectEditor  &p_object_editor;
    };
}
#endif // R3DEDITOR_MOUSE_CONTROL_H
