#ifndef R3DEDITOR_TYPES_H
#define R3DEDITOR_TYPES_H

#include <list>
#include <vector>
#include <memory>

namespace r3deditor
{
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

    class Object
    {
    public:
        //for WireframePainter
        virtual EdgeList&   edgeList() = 0;
        virtual VertexList& vertexList() = 0;
    };

    typedef std::list<std::unique_ptr<Object>> Scene;
}

#endif // R3DEDITOR_TYPES_H
