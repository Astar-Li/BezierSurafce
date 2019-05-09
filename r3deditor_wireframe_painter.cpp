#include <QPainter>

#include "r3deditor_wireframe_painter.h"

using namespace r3deditor;

WireframePainter::WireframePainter(QImage &image_bufer):
    image_bufer(image_bufer)
{

}

void WireframePainter::drawEdges(const EdgeList &edge_list, const VertexList &vertex_list, Camera &camera)
{
    QPainter qpainter;
    qpainter.begin(&image_bufer);
    qpainter.setPen(QColor(VIEWPORT_WIREFRAME_EDGE_COLOR));

    Vertex2D  v2d_1, v2d_2;

    for (auto& edge : edge_list)
    {
        //get points
        v2d_1 = camera.apply(vertex_list[edge.v1]);
        v2d_2 = camera.apply(vertex_list[edge.v2]);

        //draw line
        qpainter.drawLine(v2d_1.x, v2d_1.y, v2d_2.x, v2d_2.y);
    }

    qpainter.end();
}
