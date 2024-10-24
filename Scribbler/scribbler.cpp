#include "scribbler.h"

#include <QtWidgets>

MouseEvent::MouseEvent(int _action, QPointF _pos, quint64 _time)
    :action(_action),pos(_pos),time(_time) {}

MouseEvent::MouseEvent() {}

QDataStream &operator<<(QDataStream &out, const MouseEvent &evt) {
    return out << evt.action << evt.pos << evt.time;
}

QDataStream &operator>>(QDataStream &in, MouseEvent &evt) {
    return in >> evt.action >> evt.pos >> evt.time;
}

Scribbler::Scribbler():lineWidth(4.0),dotsOnly(false) {
    setScene(&scene);
    setSceneRect(QRectF(0.0, 0.0, 800.0, 600.0));
    setMinimumSize(QSize(800,600));
    setRenderHint(QPainter::Antialiasing, true);
    setBackgroundBrush(Qt::white);

    scene.addRect(sceneRect());
}

void Scribbler::mousePressEvent(QMouseEvent *evt) {
    QGraphicsView::mousePressEvent(evt);

    QPointF p = mapToScene(evt->pos());
    lastPoint = p;
    scene.addEllipse(QRectF(p - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);

    if (events.isEmpty()) {
        firstTimeStamp = evt->timestamp();
    }
    events << MouseEvent(MouseEvent::Press, p, evt->timestamp() - firstTimeStamp);
}

void Scribbler::mouseMoveEvent(QMouseEvent *evt) {
    QGraphicsView::mouseMoveEvent(evt);

    QPointF p = mapToScene(evt->pos());

    if (dotsOnly == true) {
        scene.addEllipse(QRectF(p - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
    } else {
        scene.addLine(QLineF(lastPoint, p), QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::FlatCap));
        scene.addEllipse(QRectF(p - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
    }

    lastPoint = p;

    events << MouseEvent(MouseEvent::Move, p, evt->timestamp() - firstTimeStamp);
}

void Scribbler::mouseReleaseEvent(QMouseEvent *evt) {
    QGraphicsView::mouseReleaseEvent(evt);

    QPointF p = mapToScene(evt->pos());

    events << MouseEvent(MouseEvent::Release, p, evt->timestamp() - firstTimeStamp);
}

void Scribbler::showAllDrawing(QList<QList<MouseEvent>> savedEvents) {
    dotsOnly = false;

    for (int event = 1; event < events.length(); ++event) {
        if (events[event].action != 1) continue;
        scene.addLine(QLineF(events[event-1].pos, events[event].pos), QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::FlatCap));
    }

    for (int listIndex = 0; listIndex < savedEvents.length(); ++listIndex) {
        for (int index = 1; index < savedEvents[listIndex].length(); ++index) {
            if (savedEvents[listIndex][index].action != 1) continue;
            scene.addLine(QLineF(savedEvents[listIndex][index - 1].pos, savedEvents[listIndex][index].pos), QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::FlatCap));
        }
    }
}

void Scribbler::showDotsOnly(QList<QList<MouseEvent>> savedEvents) {
    dotsOnly = true;

    scene.clear();

    for (int event = 0; event < events.length(); ++event) {
        scene.addEllipse(QRectF(events[event].pos - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
    }

    for (int listIndex = 0; listIndex < savedEvents.length(); ++listIndex) {
        for (int index = 0; index < savedEvents[listIndex].length(); ++index) {
            scene.addEllipse(QRectF(savedEvents[listIndex][index].pos - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
        }
    }
}

void Scribbler::sendData() {
    if (events.isEmpty()) return;

    emit dataSent(events);

    events.clear();
}

void Scribbler::resetScribbler() {
    events.clear();

    scene.clear();

    emit clearScribbler();
}

void Scribbler::redrawScribbler(QList<QList<MouseEvent>> loadedEvents) {

    for (int listIndex = 0; listIndex < loadedEvents.length(); ++listIndex) {
        for (int index = 0; index < loadedEvents[listIndex].length(); ++index) {
            if (loadedEvents[listIndex][index].action == 0) {
                scene.addEllipse(QRectF(loadedEvents[listIndex][index].pos - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
            }
            if (loadedEvents[listIndex][index].action == 1) {
                scene.addLine(QLineF(loadedEvents[listIndex][index-1].pos, loadedEvents[listIndex][index].pos), QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::FlatCap));
                scene.addEllipse(QRectF(loadedEvents[listIndex][index].pos - QPointF(0.5*lineWidth, 0.5*lineWidth), QSizeF(lineWidth, lineWidth)), Qt::NoPen, Qt::black);
            }
        }
    }
}
