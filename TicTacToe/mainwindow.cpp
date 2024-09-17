#include "mainwindow.h"

#include <QtWidgets>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isX(true) {

    QWidget *center = new QWidget();
    setCentralWidget(center);

    QGridLayout *mainLayout = new QGridLayout(center);

    displaytl = new QLineEdit("");
    displaytl->setReadOnly(true);
    displaytl->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaytl,1,1);

    displaytm = new QLineEdit("");
    displaytm->setReadOnly(true);
    displaytm->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaytm,1,2);

    displaytr = new QLineEdit("");
    displaytr->setReadOnly(true);
    displaytr->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaytr,1,3);

    displayml = new QLineEdit("");
    displayml->setReadOnly(true);
    displayml->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displayml,2,1);

    displaymm = new QLineEdit("");
    displaymm->setReadOnly(true);
    displaymm->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaymm,2,2);

    displaymr = new QLineEdit("");
    displaymr->setReadOnly(true);
    displaymr->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaymr,2,3);

    displaybl = new QLineEdit("");
    displaybl->setReadOnly(true);
    displaybl->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaybl,3,1);

    displaybm = new QLineEdit("");
    displaybm->setReadOnly(true);
    displaybm->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaybm,3,2);

    displaybr = new QLineEdit("");
    displaybr->setReadOnly(true);
    displaybr->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(displaybr,3,3);

    topLeft = new QPushButton("Tic");
    mainLayout->addWidget(topLeft,4,1);
    connect(topLeft, &QPushButton::clicked, this, &MainWindow::topLeftPressed);

    topMiddle = new QPushButton("Tac");
    mainLayout->addWidget(topMiddle,4,2);
    connect(topMiddle, &QPushButton::clicked, this, &MainWindow::topMiddlePressed);

    topRight = new QPushButton("Toe");
    mainLayout->addWidget(topRight,4,3);
    connect(topRight, &QPushButton::clicked, this, &MainWindow::topRightPressed);

    middleLeft = new QPushButton("Tic");
    mainLayout->addWidget(middleLeft,5,1);
    connect(middleLeft, &QPushButton::clicked, this, &MainWindow::middleLeftPressed);

    middleMiddle = new QPushButton("Tac");
    mainLayout->addWidget(middleMiddle,5,2);
    connect(middleMiddle, &QPushButton::clicked, this, &MainWindow::middleMiddlePressed);

    middleRight = new QPushButton("Toe");
    mainLayout->addWidget(middleRight,5,3);
    connect(middleRight, &QPushButton::clicked, this, &MainWindow::middleRightPressed);

    bottomLeft = new QPushButton("Tic");
    mainLayout->addWidget(bottomLeft,6,1);
    connect(bottomLeft, &QPushButton::clicked, this, &MainWindow::bottomLeftPressed);

    bottomMiddle = new QPushButton("Tac");
    mainLayout->addWidget(bottomMiddle,6,2);
    connect(bottomMiddle, &QPushButton::clicked, this, &MainWindow::bottomMiddlePressed);

    bottomRight = new QPushButton("Toe");
    mainLayout->addWidget(bottomRight,6,3);
    connect(bottomRight, &QPushButton::clicked, this, &MainWindow::bottomRightPressed);
}

MainWindow::~MainWindow() {}

void MainWindow::topLeftPressed() {
    topLeft->setEnabled(false);

    if(isX) {
        displaytl->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaytl->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::topMiddlePressed() {
    topMiddle->setEnabled(false);

    if(isX) {
        displaytm->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaytm->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::topRightPressed() {
    topRight->setEnabled(false);

    if(isX) {
        displaytr->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaytr->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::middleLeftPressed() {
    middleLeft->setEnabled(false);

    if(isX) {
        displayml->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displayml->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::middleMiddlePressed() {
    middleMiddle->setEnabled(false);

    if(isX) {
        displaymm->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaymm->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::middleRightPressed() {
    middleRight->setEnabled(false);

    if(isX) {
        displaymr->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaymr->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::bottomLeftPressed() {
    bottomLeft->setEnabled(false);

    if(isX) {
        displaybl->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaybl->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::bottomMiddlePressed() {
    bottomMiddle->setEnabled(false);

    if(isX) {
        displaybm->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaybm->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}

void MainWindow::bottomRightPressed() {
    bottomRight->setEnabled(false);

    if(isX) {
        displaybr->setText("X");
        QMessageBox msg;
        msg.setText("Player O's turn");
        msg.exec();
    } else {
        displaybr->setText("O");
        QMessageBox msg;
        msg.setText("Player X's turn");
        msg.exec();
    }

    isX = !isX;
}
