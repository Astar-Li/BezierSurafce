#ifndef R3DEDITOR_VIEWPORT_H
#define R3DEDITOR_VIEWPORT_H

#include "imagewidget.h"
#include "r3deditor.h"
#include "observer.h"

class R3DEditorViewport : public ImageWidget, public Observer
{
public:
    R3DEditorViewport(r3deditor::R3DEditor &r3d_editor);
    void handleNotification();
private:
    bool event(QEvent *event);
    r3deditor::R3DEditor &r3d_editor;
};


#endif // R3DEDITOR_VIEWPORT_H
