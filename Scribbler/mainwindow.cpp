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
    connect(resetScribble, &QAction::triggered, scribbler, &Scribbler::resetScribbler);

    openFile = new QAction("Open file");
    openFile->setShortcut(Qt::CTRL | Qt::Key_O);
    save = new QAction("Save");
    save->setShortcut(Qt::CTRL | Qt::Key_S);

    startCapture = new QAction("Start capture");
    startCapture->setShortcut(Qt::CTRL | Qt::Key_C);

    endCapture = new QAction("End capture");
    endCapture->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(endCapture, &QAction::triggered, scribbler, &Scribbler::sendData);

    lineSegments = new QAction("Line segments");
    lineSegments->setShortcut(Qt::CTRL | Qt::Key_L);
    connect(lineSegments, &QAction::triggered, scribbler, &Scribbler::showAllDrawing);

    dotsOnly = new QAction("Dots only");
    dotsOnly->setShortcut(Qt::CTRL | Qt::Key_D);
    connect(dotsOnly, &QAction::triggered, scribbler, &Scribbler::showDotsOnly);

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

    connect(scribbler, &Scribbler::dataSent, this, &MainWindow::dataSent);

    connect(scribbler, &Scribbler::clearScribbler, this, &MainWindow::clearData);
}

MainWindow::~MainWindow() {}

void MainWindow::dataSent(MouseEvent event) {

    storedEvents.append(event);

    QTableWidget *table = new QTableWidget();
    table->setRowCount(1);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Action","Position","Time"});
    table->verticalHeader()->hide();

    QTableWidgetItem *item = new QTableWidgetItem();
    if (event.action == 0) {
        item->setData(Qt::DisplayRole, "Press");
    }
    else if (event.action == 1) {
        item->setData(Qt::DisplayRole, "Move");
    }
    else  {
        item->setData(Qt::DisplayRole, "Release");
    }
    table->setItem(0,0,item);

    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setData(Qt::DisplayRole, QString("(%1,%2)").arg(event.pos.x()).arg(event.pos.y()));
    table->setItem(0,1,item2);

    QTableWidgetItem *item3 = new QTableWidgetItem();
    item3->setData(Qt::DisplayRole, event.time);
    table->setItem(0,2,item3);

    tab->addTab(table,QString::number(storedEvents.length(),10));
    tab->show();
}

void MainWindow::clearData() {
    storedEvents.clear();
    tab->clear();
    tab->hide();
}








