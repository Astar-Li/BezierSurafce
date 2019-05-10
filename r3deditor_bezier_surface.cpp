#include <exception>

#include <QPainter>
#include <QDebug>

#include "r3deditor_bezier_surface.h"

using namespace r3deditor;
using namespace r3deditor::Objects;

//Creates edge list of an un*vn mesh, which stores vertexes in 1D vector
r3deditor::EdgeList buildEdgeList(int un, int vn)
{
    r3deditor::EdgeList edge_list;
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

    return edge_list;
}

BezierSurface::BezierSurface(BezierSurfaceBMatrix &Bref)
{
    //B = Bref
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            B_[i][j] = Bref[i][j];
    wireframeRebuild();
}

ObjectEditor* BezierSurface::editorCreate()
{
    return new BezierSurfaceEditor(*this);
}

// Main parametric equation of the Bezier Surface
// r(u,v) = UMB(M^T)V
// note (for bicubic Bezier Surface, which is implemented here):
// v = [1, v, v2, v3]^T
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
           UMBx[i] += UM[j] * B_[j][i].x;
           UMBy[i] += UM[j] * B_[j][i].y;
           UMBz[i] += UM[j] * B_[j][i].z;
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

void BezierSurface::wireframeRebuild()
{
    const double du = 0.1;
    const double dv = 0.1;
    int un = 0;
    int vn = 0;

    vertex_list.clear();
    //edge_list.clear();

    // I.
    // adding mesh vertexes.
    for (double v = 0; v <= 1.0; v += dv)
        for (double u = 0; u <= 1.0; u += du)
            vertex_list.push_back(r(u,v));


    // surface mesh resoultion (un x vn) calc
    for (double v = 0; v <= 1.0; v += dv, ++vn);
    for (double u = 0; u <= 1.0; u += du, ++un);

    // II.
    // adding polygons
    edge_list = buildEdgeList(un, vn);
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

    notifyObservers();
}

Vertex3D BezierSurface::B(short int i, short int j)
{
    if (!((0 <= i) && (i < 4) && (0 <= j) && (j < 4)))
        throw std::range_error("In call of Vertex3D BezierSurfaceEditor::B(short int i, short int j) \
                                - invalid i or j");
    return B_[i][j];
}

void BezierSurface::setB(short int i, short int j, Vertex3D value)
{
    if (!((0 <= i) && (i < 4) && (0 <= j) && (j < 4)))
        throw std::range_error("In call of Vertex3D BezierSurfaceEditor::B(short int i, short int j) \
                                - invalid i or j");
    B_[i][j] = value;
    wireframeRebuild();
}

BezierSurfaceEditor::BezierSurfaceEditor(BezierSurface &bezier_surface) :
    ObjectEditor (bezier_surface)
{

}

void BezierSurfaceEditor::paintTo(QImage &image_buf, Camera &camera)
{
    static EdgeList   edge_list = buildEdgeList(4, 4);
    static VertexList vertex_list;
    static BezierSurface &bezier_surface = static_cast<BezierSurface&>(object);
    static QPainter qpainter;

    //get vertex list
    vertex_list.clear();
    for (short int i = 0; i < 4; i++)
        for (short int j = 0; j < 4; j++)
            vertex_list.push_back(bezier_surface.B(i,j));



    qpainter.begin(&image_buf);
    //draw edges
    qpainter.setPen(QColor(202, 255, 40));
    Vertex2D v1, v2;
    for (auto& edge : edge_list)
    {
        v1 = camera.apply(vertex_list[edge.v1]);
        v2 = camera.apply(vertex_list[edge.v2]);

        qpainter.drawLine(v1.x, v1.y, v2.x, v2.y);
    }

    //draw vertexes
    qpainter.setPen(Qt::green);
    qpainter.setBrush(Qt::green);
    Vertex2D v;
    for (auto &vertex : vertex_list)
    {
        v = camera.apply(vertex);
        qpainter.drawEllipse(QPointF(v.x, v.y), CONTROL_CIRCLE_RADIUS, CONTROL_CIRCLE_RADIUS);
    }

    qpainter.end();
}

void BezierSurfaceEditor::mouseEvent(QMouseEvent *event, Camera &camera)
{
    static BezierSurface &bezier_surface = static_cast<BezierSurface&>(object);

    //Bezier Surface B matrix projection
    static Vertex2D B_2d[4][4];
    static int click_x1;
    static int click_y1;
    static bool left_button_pressed = false;
    static bool hit = false;
    static short int  hit_i;
    static short int  hit_j;
    static Vertex3D hit_B_vertex;
    if ((event->type() == QEvent::MouseButtonPress) && (event->button() == Qt::LeftButton))
    {
        left_button_pressed = true;
        click_x1 = event->pos().rx();
        click_y1 = event->pos().ry();

        //calc projection of B points to viewport
        for (short int i = 0; i < 4; i++)
            for (short int j = 0; j < 4; j++)
                B_2d[i][j] = camera.apply(bezier_surface.B(i,j));

        // create matrix, in which every [i][j] element defines
        // the square of distance between mouse click and B[i][j] point
        // click_to_every_B_point_distance_squared = (B[i][j].x - click_x)^2 + (B[i][j].y - click_y)^2
        double click_to_every_B_point_distance_squared[4][4];
        for (short int i = 0; i < 4; i++)
            for (short int j = 0; j < 4; j++)
                click_to_every_B_point_distance_squared[i][j] =
                        (B_2d[i][j].x - click_x1)*(B_2d[i][j].x - click_x1)
                      + (B_2d[i][j].y - click_y1)*(B_2d[i][j].y - click_y1);

        // find mouse to B point hit
        for (short int i = 0; (i < 4) && (!hit); i++)
            for (short int j = 0; (j < 4) && (!hit); j++)
                if (click_to_every_B_point_distance_squared[i][j] <= CONTROL_CIRCLE_RADIUS * CONTROL_CIRCLE_RADIUS)
                {
                    hit = true;
                    hit_i = i;
                    hit_j = j;
                    hit_B_vertex = bezier_surface.B(hit_i, hit_j);
                }
    }
    if ((event->type() == QEvent::MouseMove)&&(left_button_pressed))
    {
        if (hit)
        {
            int dx = event->pos().rx() - click_x1;
            int dy = event->pos().ry() - click_y1;

            QQuaternion camera_quaternion_inverted = camera.quaternion().inverted();
            QVector3D move_vector = camera_quaternion_inverted.rotatedVector(QVector3D(dx,dy, 0));

            bezier_surface.setB(hit_i, hit_j, {hit_B_vertex.x + move_vector.x(),
                                               hit_B_vertex.y + move_vector.y(),
                                               hit_B_vertex.z + move_vector.z()});
        }
    }
    if ((event->type() == QEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton))
    {
        hit = false;
        left_button_pressed = false;
    }

}
