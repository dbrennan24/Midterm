#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "scribbler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

 public slots:
    void dataSent(QList<MouseEvent> eventList);
    void clearData();
    void saveData();
    void openFileSlot();
};
#endif // MAINWINDOW_H
