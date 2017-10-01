#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);

    void setImage(const QImage &image);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QGraphicsScene *scene;
};

#endif // IMAGEVIEW_H
