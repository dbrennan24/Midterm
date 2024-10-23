#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "scribbler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString lastDir;

    QTabWidget *tab;

    QMenu *fileMenu;
    QMenu *captureMenu;
    QMenu *viewMenu;

    QAction *resetScribble;
    QAction *openFile;
    QAction *save;
    QAction *startCapture;
    QAction *endCapture;
    QAction *lineSegments;
    QAction *dotsOnly;

    QList<QList<MouseEvent>> storedEvents;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void lineSignal(QList<QList<MouseEvent>>);
    void dotSignal(QList<QList<MouseEvent>>);
    void redrawScribbler(QList<QList<MouseEvent>>);

 public slots:
    void convertToLines();
    void convertToDots();
    void dataSent(QList<MouseEvent> eventList);
    void clearData();
    void saveData();
    void openFileSlot();
    void startCaptureSlot();
};
#endif // MAINWINDOW_H
