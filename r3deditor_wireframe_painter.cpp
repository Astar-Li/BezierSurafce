#include <QPainter>

#include "r3deditor_wireframe_painter.h"

using namespace r3deditor;

WireframePainter::WireframePainter(Scene &scene, QImage &image_bufer, Camera &camera):
    scene(scene),
    image_bufer(image_bufer),
    camera(camera)
{
}

void WireframePainter::perform()
{
    QPainter qpainter;
    qpainter.begin(&image_bufer);
    qpainter.setBrush(QBrush(Qt::black));

    Vertex2D v1, v2;
    for (auto& object : scene)
        for (auto& edge : object->edgeList())
        {
            v1 = camera.apply(object->vertexList()[edge.v1]);
            v2 = camera.apply(object->vertexList()[edge.v2]);

            qpainter.drawLine(v1.x, v1.y, v2.x, v2.y);
        }

    qpainter.end();
}
