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

namespace r3deditor
{
    //FACADE
    class R3DEditor : public Observable, public Observer
    {
    public:
        R3DEditor();
        virtual ~R3DEditor();
        void setImageBuferSize(int w, int h);
        void editObject(int i);
        void addBezierSurface(Objects::BezierSurfaceBMatrix &B);
        // -- object editor
        bool objectEditorLoaded();
        void objectEditorMouseEvent(QMouseEvent *event);
        // -- camera
        //dx,dy
        void setCameraDx(double d);
        void setCameraDy(double d);
        void setCameraDz(double d);
        //angle
        void setCameraAngleX(double a);
        void setCameraAngleY(double a);
        void setCameraAngleZ(double a);
        double cameraAngleX();
        double cameraAngleY();
        double cameraAngleZ();
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
        PObjectEditor       p_object_editor;
        ObjectEditorPainter object_editor_painter;
    };
}

#endif // R3DEDITOR_H
