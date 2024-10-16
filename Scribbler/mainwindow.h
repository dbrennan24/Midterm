#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void showAllDrawing();
    void showDotsOnly();
};
#endif // MAINWINDOW_H
