#ifndef RDEDITOR_OBJECT_H
#define RDEDITOR_OBJECT_H

#include <QMouseEvent>
#include <QImage>

#include "observer.h"
#include "r3deditor_3d_types.h"
#include "r3deditor_camera.h"

namespace r3deditor
{
    class ObjectEditor;
    class Object : public Observable
    {
    public:
        //returns object's editor
        virtual ObjectEditor* editorCreate() = 0;

        //for WireframePainter
        virtual EdgeList&   edgeList() = 0;
        virtual VertexList& vertexList() = 0;
    };

    class ObjectEditor
    {
    public:
        ObjectEditor(Object &object);
        virtual void drawTo(QImage &image_buf, Camera &camera)= 0;
        virtual void mouseEvent(QMouseEvent *event, Camera &camera) = 0;
    protected:
        Object &object;
    };


    typedef ObjectEditor* PObjectEditor;
}

#endif // RDEDITOR_OBJECT_H
