#ifndef RD3EDITOR_OBJECT_EDITOR_PAINTER_H
#define RD3EDITOR_OBJECT_EDITOR_PAINTER_H

#include <QImage>

#include "r3deditor_object.h"
#include "r3deditor_3d_types.h"
#include "r3deditor_camera.h"

namespace r3deditor
{
    class ObjectEditorPainter
    {
    public:
        ObjectEditorPainter(QImage &image_buf, Camera &camera, PObjectEditor &p_object_editor);
        void perform();
    private:
        QImage &image_buf;
        PObjectEditor &p_object_editor;
        Camera &camera;
    };
}

#endif // RD3EDITOR_OBJECT_EDITOR_PAINTER_H
