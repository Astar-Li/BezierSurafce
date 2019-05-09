#include <list>
#include <memory>

#include "r3deditor.h"

using namespace r3deditor;

R3DEditor::R3DEditor() :
    //Dependency Injection (Constructor Injection)
    image_bufer(640, 480, QImage::Format_RGB32),
    axis_painter(image_bufer, camera_),
    p_object_editor(nullptr)
{
    camera_.addObserver(*this);
}

R3DEditor::~R3DEditor()
{
    if (p_object_editor)
        delete p_object_editor;
}

void R3DEditor::objectEditorPaintTo(QImage &image_bufer)
{
    if (p_object_editor)
        p_object_editor->paintTo(image_bufer, camera_);
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

void R3DEditor::editObject(int i)
{
    if (p_object_editor)
        delete p_object_editor;
    p_object_editor = scene[i]->editorCreate();
}

Camera& R3DEditor::camera()
{
    return camera_;
}

int R3DEditor::objects_n()
{
    return scene.size();
}

bool R3DEditor::objectEditorLoaded()
{
    if (p_object_editor)
        return true;
    else
        return false;
}

void R3DEditor::objectEditorMouseEvent(QMouseEvent *event)
{
    if (p_object_editor)
        p_object_editor->mouseEvent(event, camera_);
}

VertexList R3DEditor::object_vertex_list(int i)
{
    return scene[i]->vertexList();
}

EdgeList R3DEditor::object_edge_list(int i)
{
    return scene[i]->edgeList();
}



