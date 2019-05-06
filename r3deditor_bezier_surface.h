#ifndef R3DEDITOR_BEZIER_SURFACE_H
#define R3DEDITOR_BEZIER_SURFACE_H

#include "r3deditor_3d_types.h"

namespace r3deditor
{
    namespace Objects
    {
        typedef Vertex3D BezierSurfaceBMatrix[4][4];

        class BezierSurface : public Object
        {
        public:
            BezierSurface(BezierSurfaceBMatrix &Bref);

            //for WireframePainter
            EdgeList&   edgeList();
            VertexList& vertexList();
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
    }
}

#endif // R3DEDITOR_BEZIER_SURFACE_H
