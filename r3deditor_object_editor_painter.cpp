#include "r3deditor_object_editor_painter.h"

using namespace r3deditor;

ObjectEditorPainter::ObjectEditorPainter(QImage &image_buf, Camera &camera, PObjectEditor &p_object_editor) :
    image_buf(image_buf),
    p_object_editor(p_object_editor),
    camera(camera)
{

}
void ObjectEditorPainter::perform()
{
    if (p_object_editor)
        p_object_editor->drawTo(image_buf, camera);
}
