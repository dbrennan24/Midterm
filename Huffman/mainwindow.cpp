#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), frequencies(256,0) {

    QWidget *center = new QWidget();
    setCentralWidget(center);

    QVBoxLayout *mainLayout = new QVBoxLayout(center);
    QHBoxLayout *buttonBox = new QHBoxLayout;

    openButton = new QPushButton("Open file");
    buttonBox->addWidget(openButton);
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openClicked);

    encodeButton = new QPushButton("Encode");
    buttonBox->addWidget(encodeButton);
    connect(encodeButton, &QPushButton::clicked, this, &MainWindow::encodeClicked);

    decodeButton = new QPushButton("Decode");
    buttonBox->addWidget(decodeButton);
    connect(decodeButton, &QPushButton::clicked, this, &MainWindow::decodeClicked);

    mainLayout->addLayout(buttonBox);

    table = new QTableWidget();
    table->setRowCount(256);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Code","Character","Frequency","Encoding"});
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    for (int i = 0; i < 256; ++i) table->hideRow(i);

    mainLayout->addWidget(table);

}

void MainWindow::openClicked() {
    QString fName = QFileDialog::getOpenFileName(this, "Please select file to open");

    if (fName.isEmpty()) return;
    QFile inFile(fName);

    if (!inFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Error", QString("Can't open file \"%1\"").arg(fName));
        return;
    }

    data = inFile.readAll();
    if (data.isEmpty()) {
        QMessageBox::information(this, "Empty file", "Your file is empty");
        return;
    }

    for (int pos = 0; pos < data.length(); ++pos) {
        ++frequencies[(unsigned char) data[pos]];
    }

    // Checks that there are multiple characters in the file
    int charCount = 0;
    for (int uniqueChar = 0; uniqueChar < 256; ++uniqueChar) {
        if (frequencies[uniqueChar] > 0)
            ++charCount;
    }

    if (charCount == 0) {
        QMessageBox::information(this, "File unusable",  "File only contains one symbol");
        return;
    }

    for (int index = 0; index < 256; ++index) {
        if (frequencies[index] == 0) continue;

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole,index);
        table->setItem(index,0,item);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setData(Qt::DisplayRole,QByteArray(1,index));
        table->setItem(index,1,item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setData(Qt::DisplayRole,frequencies[index]);
        table->setItem(index,2,item3);

        table->showRow(index);
    }

    table->horizontalHeader()->show();
    table->hideColumn(3);
}

void MainWindow::encodeClicked() {
    QMultiMap<int, QByteArray> toDo;
    for (int code = 0; code < 256; ++code) {
        if (frequencies[code] > 0)
            toDo.insert(frequencies[code],QByteArray(1,code));
    }

    QMap<QByteArray, QPair<QByteArray, QByteArray>> parentChildren;

    while (toDo.size() > 1) {
        int freq0 = toDo.begin().key();
        QByteArray char0 = toDo.begin().value();
        toDo.erase(toDo.begin());

        int freq1 = toDo.begin().key();
        QByteArray char1 = toDo.begin().value();
        toDo.erase(toDo.begin());

        int parentFreq = freq0 + freq1;
        QByteArray parentChars = char0 + char1;
        toDo.insert(parentFreq, parentChars);

        parentChildren[parentChars] = qMakePair(char0, char1);
    }

    QVector<QString> charEncoding(256,"");

    for (int code = 0; code < 256; ++code) {
        if (frequencies[code] == 0) continue;

        QByteArray current = toDo.begin().value();
        QString encoding = "";
        QByteArray target = QByteArray(1,code);

        while (current != target) {
            if (parentChildren[current].first.contains(target)) {
                    current = parentChildren[current].first;
                    encoding.append("0");
            } else {
                    encoding.append("1");
                    current = parentChildren[current].second;
            }
        }

        charEncoding[code] = encoding;
    }

    for (int encoding = 0; encoding < 256; ++encoding) {
        if (charEncoding[encoding] == "") continue;
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole,charEncoding[encoding]);
        table->setItem(encoding,3,item);
    }

    table->showColumn(3);

    QString stringEncoding = "";

    for (int index = 0; index < data.length(); ++index) {
        stringEncoding.append(charEncoding[(unsigned char) data[index]]);
    }

    // Working unencoded write to file:
    // QString outName = QFileDialog::getSaveFileName(this, "Save");
    // if (outName.isEmpty()) return;

    // QFile outFile(outName);

    // if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    //     QMessageBox::information(this, "Error", QString("Can't write to file \"%1\"").arg(outName));
    //     return;
    // }

    // QDataStream out(&outFile);

    // out << stringEncoding;
    // out << charEncoding;

    int nBits = stringEncoding.length();

    QByteArray bytes = *new QByteArray((nBits + 1)/8,0);

    bool ok;
    for (int i = 0; i < nBits; i+=8) {
        bytes[i/8] = stringEncoding.mid(i, 8).toInt(&ok, 2);
    }

    QString outName = QFileDialog::getSaveFileName(this, "Save");
    if (outName.isEmpty()) return;

    QFile outFile(outName);

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(this, "Error", QString("Can't write to file \"%1\"").arg(outName));
        return;
    }

    QDataStream out(&outFile);

    out << nBits;
    out << bytes;
    out << charEncoding;
}

void MainWindow::decodeClicked() {
    QString inName = QFileDialog::getOpenFileName(this, "Open file");

    QFile inFile(inName);

    inFile.open(QIODevice::ReadOnly);

    QDataStream in(&inFile);

    int nBits;
    QByteArray bytes;
    QVector<QString> charEncoding;

    in >> nBits;
    in >> bytes;
    in >> charEncoding;


    // Working unencoded read from file:
    // QString encoding;
    // QVector<QString> charEncoding;

    // in >> encoding;
    // in >> charEncoding;

    // for (int index = 0; index < 256; ++index) {\
    //     if (charEncoding[index] == "") continue;

    //     QTableWidgetItem *item = new QTableWidgetItem();
    //     item->setData(Qt::DisplayRole,index);
    //     table->setItem(index,0,item);

    //     QTableWidgetItem *item2 = new QTableWidgetItem();
    //     item2->setData(Qt::DisplayRole,QByteArray(1,index));
    //     table->setItem(index,1,item2);

    //     QTableWidgetItem *item3 = new QTableWidgetItem();
    //     item3->setData(Qt::DisplayRole,charEncoding[index]);
    //     table->setItem(index,3,item3);

    //     table->showRow(index);
    // }

    // table->horizontalHeader()->show();

    // QString outName = QFileDialog::getSaveFileName(this, "Save");
    // if (outName.isEmpty()) return;

    // QFile outFile(outName);

    // if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    //     QMessageBox::information(this, "Error", QString("Can't write to file \"%1\"").arg(outName));
    //     return;
    // }

    // QDataStream out(&outFile);

    // out << encoding;
    // out << charEncoding;
}

MainWindow::~MainWindow() {}









