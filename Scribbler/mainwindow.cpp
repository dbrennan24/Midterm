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
    connect(openFile, &QAction::triggered, scribbler, &Scribbler::resetScribbler);
    connect(openFile, &QAction::triggered, this, &MainWindow::openFileSlot);

    save = new QAction("Save");
    save->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(save, &QAction::triggered, this, &MainWindow::saveData);

    startCapture = new QAction("Start capture");
    startCapture->setShortcut(Qt::CTRL | Qt::Key_C);
    connect(startCapture, &QAction::triggered, this, &MainWindow::startCaptureSlot);

    endCapture = new QAction("End capture");
    endCapture->setDisabled(true);
    endCapture->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(endCapture, &QAction::triggered, scribbler, &Scribbler::sendData);

    lineSegments = new QAction("Line segments");
    lineSegments->setShortcut(Qt::CTRL | Qt::Key_L);
    connect(lineSegments, &QAction::triggered, this, &MainWindow::convertToLines);
    connect(this, &MainWindow::lineSignal, scribbler, &Scribbler::showAllDrawing);

    dotsOnly = new QAction("Dots only");
    dotsOnly->setShortcut(Qt::CTRL | Qt::Key_D);
    connect(dotsOnly, &QAction::triggered, this, &MainWindow::convertToDots);
    connect(this, &MainWindow::dotSignal, scribbler, &Scribbler::showDotsOnly);

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

    connect(this, &MainWindow::redrawScribbler, scribbler, &Scribbler::redrawScribbler);

    QSettings settings("DB", "Midterm");
    lastDir = settings.value("lastDir", "").toString();
}

MainWindow::~MainWindow() {
    QSettings settings("DB", "Midterm");
    settings.setValue("lastDir", lastDir);
}

void MainWindow::convertToLines() {
    emit lineSignal(storedEvents);
}

void MainWindow::convertToDots() {
    emit dotSignal(storedEvents);
}

void MainWindow::dataSent(QList<MouseEvent> eventList) {
    storedEvents.append(eventList);

    QTableWidget *table = new QTableWidget();
    table->setRowCount(eventList.length());
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Action","Position","Time"});
    table->verticalHeader()->hide();

    for (int index = 0; index < eventList.length(); ++index) {
        QTableWidgetItem *item = new QTableWidgetItem();
        if (eventList[index].action == 0) {
            item->setData(Qt::DisplayRole, "Press");
        }
        else if (eventList[index].action == 1) {
            item->setData(Qt::DisplayRole, "Move");
        }
        else  {
            item->setData(Qt::DisplayRole, "Release");
        }
        table->setItem(index,0,item);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setData(Qt::DisplayRole, QString("(%1,%2)").arg(eventList[index].pos.x()).arg(eventList[index].pos.y()));
        table->setItem(index,1,item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setData(Qt::DisplayRole, eventList[index].time);
        table->setItem(index,2,item3);
    }

    tab->addTab(table,QString::number(storedEvents.length(),10));
    tab->show();
}

void MainWindow::clearData() {
    storedEvents.clear();
    tab->clear();
    tab->hide();
}

void MainWindow::saveData() {
    QString outName = QFileDialog::getSaveFileName(this, "Save");
    if (outName.isEmpty()) return;

    lastDir = QFileInfo(outName).absolutePath();

    QFile outFile(outName);

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(this, "Error", QString("Can't write to file \"%1\"").arg(outName));
        return;
    }

    QDataStream out(&outFile);

    out << storedEvents;
}

void MainWindow::openFileSlot() {
    QString inName = QFileDialog::getOpenFileName(this, "Open file");

    lastDir = QFileInfo(inName).absolutePath();

    QFile inFile(inName);

    inFile.open(QIODevice::ReadOnly);

    QDataStream in(&inFile);

    QList<QList<MouseEvent>> savedEvents;

    in >> savedEvents;

    for (int listIndex = 0; listIndex < savedEvents.length(); ++listIndex) {
        QTableWidget *table = new QTableWidget();
        table->setRowCount(savedEvents[listIndex].length());
        table->setColumnCount(3);
        table->setHorizontalHeaderLabels({"Action","Position","Time"});
        table->verticalHeader()->hide();

        for (int index = 0; index < savedEvents[listIndex].length(); ++index) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (savedEvents[listIndex][index].action == 0) {
                item->setData(Qt::DisplayRole, "Press");
            }
            else if (savedEvents[listIndex][index].action == 1) {
                item->setData(Qt::DisplayRole, "Move");
            }
            else  {
                item->setData(Qt::DisplayRole, "Release");
            }
            table->setItem(index,0,item);

            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setData(Qt::DisplayRole, QString("(%1,%2)").arg(savedEvents[listIndex][index].pos.x()).arg(savedEvents[listIndex][index].pos.y()));
            table->setItem(index,1,item2);

            QTableWidgetItem *item3 = new QTableWidgetItem();
            item3->setData(Qt::DisplayRole, savedEvents[listIndex][index].time);
            table->setItem(index,2,item3);
        }

        tab->addTab(table,QString::number(listIndex + 1,10));
        tab->show();

        storedEvents.append(savedEvents[listIndex]);
    }

    emit redrawScribbler(savedEvents);
}

void MainWindow::startCaptureSlot() {
    endCapture->setDisabled(false);
}
