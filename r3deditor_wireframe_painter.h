#ifndef R3DEDITOR_PAINTERS_H
#define R3DEDITOR_PAINTERS_H

#include <QQuaternion>

#include "r3deditor_3d_types.h"
#include "r3deditor_camera.h"

namespace r3deditor
{
    class WireframePainter
    {
    public:
        WireframePainter(QImage &image_bufer);
        void drawEdges(const EdgeList &edge_list, const VertexList &vertex_list, Camera &camera);
    private:
        QImage &image_bufer;
    };
}


#endif // R3DEDITOR_PAINTERS_H
