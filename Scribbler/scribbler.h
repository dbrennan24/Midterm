#ifndef SCRIBBLER_H
#define SCRIBBLER_H

#include <QGraphicsView>

class MouseEvent {
public:
    enum {
        Press,
        Move,
        Release
    };

    int action;
    QPointF pos;
    quint64 time;

    MouseEvent(int _action, QPointF _pos, quint64 _time);

    friend QDataStream &operator<<(QDataStream &out, const MouseEvent &evt);
    friend QDataStream &operator>>(QDataStream &out, MouseEvent &evt);
};

class Scribbler : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene scene;
    double lineWidth;
    QPointF lastPoint;

    QList<MouseEvent> events;

    bool dotsOnly;

public:
    Scribbler();

public slots:
    void showAllDrawing();
    void showDotsOnly();

protected:
    void mouseMoveEvent(QMouseEvent *evt) override;
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
};

#endif // SCRIBBLER_H
