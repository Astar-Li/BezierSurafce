#include <QEvent>
#include <QMouseEvent>

#include "r3deditor_viewport.h"
#include "observer.h"

using namespace r3deditor;

R3DEditorViewport::R3DEditorViewport(R3DEditor &r3d_editor) :
    r3d_editor(r3d_editor),
    image_bufer(QImage(640, 480, QImage::Format_RGB32)),
    wirefram_painter(image_bufer)
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

    //r3d_editor.editObject(0);
}

void R3DEditorViewport::update()
{
    // R3DEDITOR VIEW

    image_bufer.fill(VIEWPORT_BACKGROUND_COLOR);

    for (int i = 0; i < r3d_editor.objects_n(); i++)
        wirefram_painter.drawEdges(r3d_editor.object_edge_list(i),
                                   r3d_editor.object_vertex_list(i),
                                   r3d_editor.camera());

    ImageWidget::setImage(image_bufer);
    ImageWidget::update();
}

void R3DEditorViewport::handleNotification()
{
    update();
}

bool R3DEditorViewport::event(QEvent *event)
{
    //R3DEDITOR CONTROL

    //resize
    if (event->type() == QEvent::Resize)
    {
        image_bufer = QImage(width(), height(), QImage::Format_RGB32);
        update();
    }

    //mouse
    if ((event->type() == QEvent::MouseMove) ||
        (event->type() == QEvent::MouseButtonPress) ||
        (event->type() == QEvent::MouseButtonRelease))
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if (r3d_editor.objectEditorLoaded())
            r3d_editor.objectEditorMouseEvent(mouse_event);
        else
        {
            //rotate
            static double angle_x1, angle_z1;
            static double x1, y1;
            static bool   left_button_pressed = false;
            //mouse button pressed
            if ((event->type() == QEvent::MouseButtonPress) && (mouse_event->button() == Qt::LeftButton))
            {
                left_button_pressed = true;
                //save click's x,y and camera's x,z angles
                x1      = mouse_event->pos().rx();
                y1      = mouse_event->pos().ry();
                angle_x1 = r3d_editor.camera().angleX();
                angle_z1 = r3d_editor.camera().angleZ();
            }
            if ((event->type() == QEvent::MouseMove)&&(left_button_pressed))
            {
                double x2 = mouse_event->pos().rx();
                double y2 = mouse_event->pos().ry();

                //calc rotate angles
                double dx = x2-x1;
                double dy = y2-y1;
                double angle_x2 = -dy*ROTATE_SESITIVITY;
                double angle_z2 = -dx*ROTATE_SESITIVITY;

                //abs(angle_resx) < PI/2
                double angle_resx = angle_x1 + angle_x2;
                if (angle_resx > MATH_PI/2)
                    angle_resx = MATH_PI/2;
                if (angle_resx < -MATH_PI/2)
                    angle_resx = -MATH_PI/2;

                r3d_editor.camera().setAngleX(angle_resx);
                r3d_editor.camera().setAngleZ(angle_z1 + angle_z2);
            }
            if ((event->type() == QEvent::MouseButtonRelease) && (mouse_event->button() == Qt::LeftButton))
            {
                left_button_pressed = false;
            }
        }
    }


    ImageWidget::event(event);
    return true;
}





