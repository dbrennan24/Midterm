#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QByteArray data;
    QVector<int> frequencies;

    QPushButton *openButton;
    QPushButton *encodeButton;
    QPushButton *decodeButton;

    QTableWidget *table;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openClicked();
    void encodeClicked();
    void decodeClicked();
};
#endif // MAINWINDOW_H
