#include <list>
#include <memory>

#include "r3deditor.h"

using namespace r3deditor;

R3DEditor::R3DEditor() :
    //Dependency Injection (Constructor Injection)
    image_bufer(640, 480, QImage::Format_RGB32),
    wireframe_painter(scene, image_bufer, camera),
    mouse_control(camera)
{
    camera.addObserver(*this);
}

void R3DEditor::handleNotification()
{
    notifyObservers();
}

void R3DEditor::addBezierSurface(Objects::BezierSurfaceBMatrix &B)
{
    scene.push_back(std::unique_ptr<Object>(new Objects::BezierSurface(B)));
    notifyObservers();
}

void R3DEditor::setImageBuferSize(int w, int h)
{
    image_bufer = QImage(w, h, QImage::Format_RGB32);
    camera.setDx((double)w/2);
    camera.setDy((double)h/2);
    notifyObservers();
}

void R3DEditor::sendMouseEvent(QMouseEvent *event)
{
    mouse_control.sendEvent(event);
}

QImage& R3DEditor::imageBufer()
{
    image_bufer.fill(Qt::white);
    wireframe_painter.perform();

    return image_bufer;
}




