#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <QGraphicsView>

class ColorHistogram : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene scene;
    QImage image;
    QGraphicsPixmapItem *giPixmap;
    double scale;


public:
    ColorHistogram(const QImage &_image);

signals:
    void mouseMoved(QPoint pos, QColor color);

protected:
    void keyPressEvent(QKeyEvent *evt) override;
    void mouseMoveEvent(QMouseEvent *evt) override;
};

#endif // COLORHISTOGRAM_H
