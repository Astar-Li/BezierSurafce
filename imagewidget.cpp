#include <QEvent>
#include <QImage>
#include <QPainter>

#include "imagewidget.h"

ImageWidget::ImageWidget()
{
    pixel_map = nullptr;
}

ImageWidget::~ImageWidget()
{
    if (pixel_map)
        delete pixel_map;
}

void ImageWidget::setImage(const QImage &pm)
{
    if (pixel_map)
        delete pixel_map;
    pixel_map = new QImage(pm);
    update();
}

bool ImageWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Paint)
        if (pixel_map)
        {
            QPainter painter;
            painter.begin(this);
            painter.drawImage(0,0, static_cast<QImage>(*pixel_map));
            painter.end();
        }
    return true;
}

