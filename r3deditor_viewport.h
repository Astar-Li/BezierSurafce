#ifndef R3DEDITOR_VIEWPORT_H
#define R3DEDITOR_VIEWPORT_H

#include "imagewidget.h"
#include "r3deditor.h"
#include "observer.h"
#include "r3deditor_wireframe_painter.h"

class R3DEditorViewport : public ImageWidget, public Observer
{
public:
    R3DEditorViewport(r3deditor::R3DEditor &r3d_editor);
    void handleNotification();
    void update();
private:
    bool event(QEvent *event);
    r3deditor::R3DEditor        &r3d_editor;

    QImage                      image_bufer;
    r3deditor::WireframePainter wirefram_painter;
};


#endif // R3DEDITOR_VIEWPORT_H
