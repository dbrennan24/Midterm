#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <QtWidgets>

class ColorHistogram : public QWidget
{

    Q_OBJECT

    QImage image;

    QVector<QPixmap> slices;
    QVector<int> colors;

    QLabel *lbl;
    QLabel *xLabel;
    QLabel *yLabel;

    QSlider *slider;
    QComboBox *colorSelector;
    QLabel *sliderLabel;

public:
    ColorHistogram(const QImage &_image);

signals:
    void sliderMoved(int value);
    void currentIndexChanged(int index);

public slots:
    void updateLabelValue(int value);
    void updatePixmap(int value);
    void updateBoxColor(int index);
};

#endif // COLORHISTOGRAM_H
