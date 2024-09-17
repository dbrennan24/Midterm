#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *topLeft;
    QPushButton *topMiddle;
    QPushButton *topRight;
    QPushButton *middleLeft;
    QPushButton *middleMiddle;
    QPushButton *middleRight;
    QPushButton *bottomLeft;
    QPushButton *bottomMiddle;
    QPushButton *bottomRight;

    QLineEdit *displaytl;
    QLineEdit *displaytm;
    QLineEdit *displaytr;
    QLineEdit *displayml;
    QLineEdit *displaymm;
    QLineEdit *displaymr;
    QLineEdit *displaybl;
    QLineEdit *displaybm;
    QLineEdit *displaybr;

    bool isX;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void topLeftPressed();
    void topMiddlePressed();
    void topRightPressed();
    void middleLeftPressed();
    void middleMiddlePressed();
    void middleRightPressed();
    void bottomLeftPressed();
    void bottomMiddlePressed();
    void bottomRightPressed();
};
#endif // MAINWINDOW_H
