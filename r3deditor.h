#ifndef R3DEDITOR_H
#define R3DEDITOR_H

#include <list>
#include <memory>

#include <QImage>
#include <QMouseEvent>

#include "observer.h"
#include "r3deditor_3d_types.h"
#include "r3deditor_wireframe_painter.h"
#include "r3deditor_bezier_surface.h"
#include "r3deditor_camera.h"
#include "r3deditor_mouse_control.h"
#include "r3deditor_axis_painter.h"
#include "r3deditor_object.h"
#include "r3deditor_object_editor_painter.h"

namespace r3deditor
{
    //FACADE
    class R3DEditor : public Observable, public Observer
    {
    public:
        R3DEditor();
        virtual ~R3DEditor();
        void setImageBuferSize(int w, int h);
        void sendMouseEvent(QMouseEvent *event);
        void editObject(int i);
        void addBezierSurface(Objects::BezierSurfaceBMatrix &B);
        //view
        QImage& imageBufer();
        //handles when model changes
        virtual void handleNotification();
    private:
        QImage              image_bufer;
        Scene               scene;
        WireframePainter    wireframe_painter;
        Camera              camera;
        AxisPainter         axis_painter;
        MouseControl        mouse_control;
        PObjectEditor       p_object_editor;
        ObjectEditorPainter object_editor_painter;
    };
}

#endif // R3DEDITOR_H
