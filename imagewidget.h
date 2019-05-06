//  Image drawing widget

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QImage>
#include <QWidget>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    ImageWidget();
    ~ImageWidget();
protected:
    void setImage(const QImage &pm);
    bool event(QEvent *event);
private:
    QImage *pixel_map;
};



#endif // IMAGEWIDGET_H
