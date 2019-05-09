#include <list>
#include <memory>

#include "r3deditor.h"

using namespace r3deditor;

R3DEditor::R3DEditor() :
    //Dependency Injection (Constructor Injection)
    image_bufer(640, 480, QImage::Format_RGB32),
    wireframe_painter(scene, image_bufer, camera),
    axis_painter(image_bufer, camera),
    mouse_control(camera, p_object_editor),
    p_object_editor(nullptr),
    object_editor_painter(image_bufer, camera, p_object_editor)
{
    camera.addObserver(*this);
}

R3DEditor::~R3DEditor()
{
    if (p_object_editor)
        delete p_object_editor;
}

void R3DEditor::handleNotification()
{
    notifyObservers();
}

void R3DEditor::addBezierSurface(Objects::BezierSurfaceBMatrix &B)
{
    std::unique_ptr<Object> p_bezier_surface(new Objects::BezierSurface(B));
    p_bezier_surface->addObserver(*this);
    scene.push_back(std::move(p_bezier_surface));
}

void R3DEditor::setImageBuferSize(int w, int h)
{
    image_bufer = QImage(w, h, QImage::Format_RGB32);
    camera.setDx((double)w/2);
    camera.setDy((double)h/2);
    notifyObservers();
}

void R3DEditor::mouseEvent(QMouseEvent *event)
{
    mouse_control.mouseEvent(event);
}

void R3DEditor::editObject(int i)
{
    if (p_object_editor)
        delete p_object_editor;
    p_object_editor = scene[i]->editorCreate();
}

QImage& R3DEditor::imageBufer()
{
    image_bufer.fill(VIEWPORT_BACKGROUND_COLOR);

    wireframe_painter.perform();
    axis_painter.perform();
    object_editor_painter.perform();

    return image_bufer;
}




