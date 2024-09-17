#include "mainwindow.h"

int addOne(int &x) {
    return ++x;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    int a = 202;
    int &otherA = a;

    qDebug() << a << otherA;

    otherA = 318;

    qDebug() << a << otherA;

    addOne(a);

    qDebug() << a << otherA;

    QStringList list;

    list << "First" << "Second" << "Third";

    qDebug() << list;
}

MainWindow::~MainWindow() {}
