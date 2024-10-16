#include "mainwindow.h"

#include <QtWidgets>
#include <QMenuBar>

#include "scribbler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    QHBoxLayout *layout = new QHBoxLayout(widget);

    Scribbler *scribbler = new Scribbler();

    layout->addWidget(scribbler);

    tab = new QTabWidget();
    layout->addWidget(tab);
    tab->hide();

    resetScribble = new QAction("Reset scribble");
    resetScribble->setShortcut(Qt::CTRL | Qt::Key_R);
    openFile = new QAction("Open file");
    openFile->setShortcut(Qt::CTRL | Qt::Key_O);
    save = new QAction("Save");
    save->setShortcut(Qt::CTRL | Qt::Key_S);

    startCapture = new QAction("Start capture");
    startCapture->setShortcut(Qt::CTRL | Qt::Key_C);
    endCapture = new QAction("End capture");
    endCapture->setShortcut(Qt::CTRL | Qt::Key_E);

    lineSegments = new QAction("Line segments");
    lineSegments->setShortcut(Qt::CTRL | Qt::Key_L);
    dotsOnly = new QAction("Dots only");
    dotsOnly->setShortcut(Qt::CTRL | Qt::Key_D);

    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(resetScribble);
    fileMenu->addAction(openFile);
    fileMenu->addAction(save);

    captureMenu = menuBar()->addMenu("Capture");
    captureMenu->addAction(startCapture);
    captureMenu->addAction(endCapture);

    viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction(lineSegments);
    viewMenu->addAction(dotsOnly);
}

MainWindow::~MainWindow() {}
