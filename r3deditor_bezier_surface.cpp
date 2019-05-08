#include <QPainter>

#include "r3deditor_bezier_surface.h"

using namespace r3deditor;
using namespace r3deditor::Objects;

BezierSurface::BezierSurface(BezierSurfaceBMatrix &Bref)
{
    //B = Bref
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            B[i][j] = Bref[i][j];
    wireframeRebuild(0.09, 0.09);
}

ObjectEditor* BezierSurface::editorCreate()
{
    return new BezierSurfaceEditor(*this);
}

//main parametric equation
//parametric equation r(u,v) = UMB(M^T)V
// note: v = [1, v, v2, v3]^T
// 0 <= u <= 1, 0 <= v <= 1
Vertex3D BezierSurface::r(double u, double v)
{
    double u2 = u * u;
    double u3 = u2 * u;
    double v2 = v * v;
    double v3 = v2 * v;

    double U[4] = {1, u, u2, u3};
    double V[4] = {1, v, v2, v3};

    static const double M[4][4] = {
                       { 1, 0, 0, 0},
                       {-3, 3, 0, 0},
                       { 3,-6, 3, 0},
                       {-1, 3,-3, 1},
                       };
    //UM
    double UM[4] = {0};
    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
           UM[i] += U[j]*M[j][i];

    //UMB
    double UMBx[4] = {0};
    double UMBy[4] = {0};
    double UMBz[4] = {0};
    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
       {
           UMBx[i] += UM[j] * B[j][i].x;
           UMBy[i] += UM[j] * B[j][i].y;
           UMBz[i] += UM[j] * B[j][i].z;
       }

    //UMB(M^T)
    double UMBMtx[4] = {0};
    double UMBMty[4] = {0};
    double UMBMtz[4] = {0};
    for (int i=0; i<4; i++)
       for (int j=0; j<4; j++)
       {
           UMBMtx[i] += UMBx[j] * M[i][j];
           UMBMty[i] += UMBy[j] * M[i][j];
           UMBMtz[i] += UMBz[j] * M[i][j];
       }

    //UMB(M^T)V
    Vertex3D res = {0,0,0};
    for (int i=0; i<4; i++)
    {
       res.x += UMBMtx[i] * V[i];
       res.y += UMBMty[i] * V[i];
       res.z += UMBMtz[i] * V[i];
    }

    return res;
}

EdgeList&   BezierSurface::edgeList()
{
    return edge_list;
}

VertexList& BezierSurface::vertexList()
{
    return vertex_list;
}

void BezierSurface::wireframeRebuild(double du, double dv)
{
    vertex_list.clear();
    edge_list.clear();

    // I.
    // adding mesh vertexes.
    for (double v = 0; v <= 1.0; v += dv)
        for (double u = 0; u <= 1.0; u += du)
            vertex_list.push_back(r(u,v));


    // surface mesh resoultion (un x vn)
    int un = 0;
    int vn = 0;
    for (double v = 0; v <= 1.0; v += dv, ++vn);
    for (double u = 0; u <= 1.0; u += du, ++un);

    // II.
    // adding polygons
    /*r3deditor::Polygon poly;
    for (int v = 0; v < vn - 1; v++)
        for (int u = 0; u < un - 1; u++)
        {
            //
            //  8 - 1 - 0 - 0
            //  |   |   |   |
            //  1 - 1 - 0 - 0
            //  |   |   |   |
            //  0 - 0 - 0 - 0
            //
            // 8 - (u,v), 8-1-1-1 - polygon to add

            // i = i(u,v) = un * v + u
            // equation above is used for calculating vertex index
            // in 1D vertex_list array using (u,v) vertex
            // coordinates
            poly.vn[0] = un * v + u;
            poly.vn[1] = un * (v+1) + u;
            poly.vn[2] = un * (v+1) + (u+1);
            poly.vn[3] = un * v + (u+1);
            wireframe_->faceList().push_back(poly);
        }
    */

    // III.
    // adding edges
    // i = i(u,v) = un * v + u
    r3deditor::Edge edge_;
    int v,u;
    for (v = 0; v < vn - 1; v++)
    {
        for (u = 0; u < un - 1; u++)
        {
            //
            //  0 - 0 - 0 - 0
            //  |   |   |
            //  0 - 0 - 0 - 0
            //  |   |   |
            //  0   0   0   0
            //
            edge_.v1 = un * v + u;
            edge_.v2 = un * v + (u+1);
            edge_list.push_back(edge_);
            edge_.v1 = un * v + u;
            edge_.v2 = un * (v + 1) + u;
            edge_list.push_back(edge_);
        }
        //
        //  0 - 0 - 0 - 0
        //  |   |   |   |
        //  0 - 0 - 0 - 0
        //  |   |   |   |
        //  0   0   0   0
        //
        edge_.v1 = un * v + u;
        edge_.v2 = un * (v + 1) + u;
        edge_list.push_back(edge_);
    }
    for (u = 0; u < un - 1; u++)
    {

        //
        //  0 - 0 - 0 - 0
        //  |   |   |   |
        //  0 - 0 - 0 - 0
        //  |   |   |   |
        //  0 - 0 - 0 - 0
        //
        edge_.v1 = un * v + u;
        edge_.v2 = un * v + (u+1);
        edge_list.push_back(edge_);
    }
}

BezierSurfaceEditor::BezierSurfaceEditor(BezierSurface &bezier_surface) :
    ObjectEditor (bezier_surface)
{

}

void BezierSurfaceEditor::drawTo(QImage &image_buf, Camera &camera)
{
    image_buf.fill(Qt::red);
}
