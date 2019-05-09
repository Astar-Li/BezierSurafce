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
#include "r3deditor_axis_painter.h"
#include "r3deditor_object.h"
#include "r3deditor_object_editor_painter.h"
#include "r3deditor_scene.h"

namespace r3deditor
{
    //FACADE
    class R3DEditor : public Observable, public Observer
    {
    public:
        R3DEditor();
        virtual ~R3DEditor();
        void addBezierSurface(Objects::BezierSurfaceBMatrix &B);
        // -- object editor
        int objects_n();
        void editObject(int i);
        bool objectEditorLoaded();
        void objectEditorMouseEvent(QMouseEvent *event);
        VertexList object_vertex_list(int i);
        EdgeList   object_edge_list(int i);
        // -- camera
        Camera& camera();
        //handles when model changes
        virtual void handleNotification();
    private:
        QImage              image_bufer;
        Scene               scene;
        Camera              camera_;
        AxisPainter         axis_painter;
        PObjectEditor       p_object_editor;
        ObjectEditorPainter object_editor_painter;
    };
}

#endif // R3DEDITOR_H
