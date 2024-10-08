#include "mainwindow.h"

#include <QtWidgets>

#include "colorhistogram.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QAction *openFileAct = new QAction("&Open image file");
    connect(openFileAct, &QAction::triggered, this, &MainWindow::openFileSlot);
    openFileAct->setShortcut(Qt::CTRL | Qt::Key_O);

    QMenu *fileMenu = new QMenu("&File");
    fileMenu->addAction(openFileAct);
    menuBar()->addMenu(fileMenu);

    QSettings settings("DB","ColorHistogram");
    lastDir = settings.value("lastDir","").toString();
}

MainWindow::~MainWindow() {
    QSettings settings("DB","ColorHistogram");
    settings.setValue("lastDir", lastDir);
}

void MainWindow::openFileSlot() {
    QString fName = QFileDialog::getOpenFileName(this, "Select image file", lastDir, "Image files (*.png *.jpeg *.jpg *.bmp)");
    if (fName.isEmpty()) return;

    QImage image(fName);
    if (image.isNull()) return;

    lastDir = QFileInfo(fName).absolutePath();

    ColorHistogram *colorHistogram = new ColorHistogram(image);
    connect(colorHistogram, &ColorHistogram::mouseMoved, this, &MainWindow::mouseMoved);

    setCentralWidget(colorHistogram);
}

void MainWindow::mouseMoved(QPoint pos, QColor color) {
    statusBar()->showMessage(QString("Position  (%1,%2), Color (R,G,B) = (%3,%4,%5)").arg(pos.x()).arg(pos.y()).arg(color.red()).arg(color.green()).arg(color.blue()));
}






