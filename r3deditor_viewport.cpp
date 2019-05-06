#include <QEvent>
#include <QMouseEvent>

#include "r3deditor_viewport.h"
#include "observer.h"

using namespace r3deditor;

R3DEditorViewport::R3DEditorViewport(R3DEditor &r3d_editor) : r3d_editor(r3d_editor)
{
    r3d_editor.addObserver(*this);

    Objects::BezierSurfaceBMatrix B = {
            {{100-250,100-250, 0},   {200-250,100-250, 200}, {300-250,100-250, 200}, {400-250,100-250, 0}},
            {{100-250,200-250, 200}, {200-250,200-250, -200}, {300-250,200-250, 400}, {400-250,200-250, 200}},
            {{100-250,300-250, 200}, {200-250,300-250, 400}, {300-250,300-250, 400}, {400-250,300-250, 200}},
            {{100-250,400-250, 0},   {200-250,400-250, 200}, {300-250,400-250, 200}, {400-250,400-250, 0}},
        };

    r3d_editor.addBezierSurface(B);

    Objects::BezierSurfaceBMatrix B2 = {
            {{100-250,100-250, 0},   {200-250,100-250, 0}, {300-250,100-250, 0}, {400-250,100-250, 0}},
            {{100-250,200-250, 0}, {200-250,200-250, -0}, {300-250,200-250, 0}, {400-250,200-250, 0}},
            {{100-250,300-250, 0}, {200-250,300-250, 0}, {300-250,300-250, 0}, {400-250,300-250, 0}},
            {{100-250,400-250, 0},   {200-250,400-250, 0}, {300-250,400-250, 0}, {400-250,400-250, 0}},
        };

    r3d_editor.addBezierSurface(B2);

}

void R3DEditorViewport::handleNotification()
{
    setImage(r3d_editor.imageBufer());
}

bool R3DEditorViewport::event(QEvent *event)
{
    if (event->type() == QEvent::Resize)
        r3d_editor.setImageBuferSize(width(), height());

    if ((event->type() == QEvent::MouseMove) ||
        (event->type() == QEvent::MouseButtonPress) ||
        (event->type() == QEvent::MouseButtonRelease))
        r3d_editor.sendMouseEvent(static_cast<QMouseEvent*>(event));

    ImageWidget::event(event);
    return true;
}





