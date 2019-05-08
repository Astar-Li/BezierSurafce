#ifndef R3DEDITOR_TYPES_H
#define R3DEDITOR_TYPES_H

#include <list>
#include <vector>
#include <memory>

namespace r3deditor
{
    //should be >0 and <=1
    static const double ROTATE_SESITIVITY = 0.01;
    static const double MATH_PI = 3.141592653589793238;
    static const int    VIEWPORT_BACKGROUND_COLOR = 0x4a4f59;
    static const int    VIEWPORT_WIREFRAME_EDGE_COLOR = 0xd2d7dd;

    typedef double matrix3x3[3][3];

    struct Vertex2D
    {
        double x,y;
    };

    struct Vertex3D
    {
        double x,y,z;
    };

    struct Edge
    {
        //vertex array element indexes
        int v1, v2;
    };

    struct Polygon
    {
        //array of vertex array element indexes
        int vn[4];
    };

    typedef std::vector<Vertex3D> VertexList;
    typedef std::list<Edge>       EdgeList;
}

#endif // R3DEDITOR_TYPES_H
