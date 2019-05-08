#ifndef R3DEDITOR_BEZIER_SURFACE_H
#define R3DEDITOR_BEZIER_SURFACE_H

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

            //for WireframePainter
            EdgeList&   edgeList();
            VertexList& vertexList();
            BezierSurfaceBMatrix& BMatrix();
        private:
            //main parametric equation
            Vertex3D r(double u, double v);
            //characteristic polyhedra
            BezierSurfaceBMatrix B;

            //for WireframPainter
            void wireframeRebuild(double du, double dv);
            VertexList vertex_list;
            EdgeList   edge_list;
        };

        class BezierSurfaceEditor : public ObjectEditor
        {
        public:
            BezierSurfaceEditor(BezierSurface &bezier_surface);
            void drawTo(QImage &image_buf, Camera &camera);
        };
    }
}

#endif // R3DEDITOR_BEZIER_SURFACE_H
