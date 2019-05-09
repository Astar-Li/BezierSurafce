#ifndef R3DEDITOR_BEZIER_SURFACE_H
#define R3DEDITOR_BEZIER_SURFACE_H

#include "QMouseEvent"

#include "r3deditor_3d_types.h"
#include "r3deditor_object.h"

namespace r3deditor
{
    namespace Objects
    {
        typedef Vertex3D BezierSurfaceBMatrix[4][4];

        class BezierSurfaceEditor;
        class BezierSurface : public Object
        {
        public:
            BezierSurface(BezierSurfaceBMatrix &Bref);

            //returns BezierEditor
            ObjectEditor* editorCreate();
            Vertex3D      B(short int i, short int j);
            void          setB(short int i, short int j, Vertex3D value);

            //for WireframePainter
            EdgeList&   edgeList();
            VertexList& vertexList();
        private:
            //main parametric equation
            Vertex3D r(double u, double v);
            //characteristic polyhedra
            BezierSurfaceBMatrix B_;
            //for WireframPainter
            void wireframeRebuild();
            VertexList vertex_list;
            EdgeList   edge_list;
        };

        class BezierSurfaceEditor : public ObjectEditor
        {
        public:
            BezierSurfaceEditor(BezierSurface &bezier_surface);
            // "control"
            void mouseEvent(QMouseEvent *event, Camera &camera);
            // "view"
            void drawTo(QImage &image_buf, Camera &camera);
        private:
            static const int CONTROL_CIRCLE_RADIUS = 5;
        };
    }
}

#endif // R3DEDITOR_BEZIER_SURFACE_H
