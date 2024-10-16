#include "colorhistogram.h"

#include "imageviewer.h"

#include <QtWidgets>
#include <QPainter>

ColorHistogram::ColorHistogram(const QImage &_image):image(_image), colors(1 << 24, 0) {

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    ImageViewer *imageViewer = new ImageViewer(image);

    mainLayout->addWidget(imageViewer);

    xLabel = new QLabel("x-axis: Blue");
    verticalLayout->addWidget(xLabel);

    yLabel = new QLabel("y-axis: Red");
    verticalLayout->addWidget(yLabel);

    slices.resize(256);
    slices[0] = QPixmap(256,256);
    lbl = new QLabel();

    verticalLayout->addWidget(lbl);

    slider = new QSlider(Qt::Horizontal);
    connect(slider, &QSlider::sliderMoved, this, &ColorHistogram::updateLabelValue);
    connect(slider, &QSlider::sliderMoved, this, &ColorHistogram::updatePixmap);
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setValue(0);

    verticalLayout->addWidget(slider);

    sliderLabel = new QLabel("Slider Value: 0");

    verticalLayout->addWidget(sliderLabel);

    colorSelector = new QComboBox();
    connect(colorSelector, &QComboBox::currentIndexChanged, this, &ColorHistogram::updateBoxColor);
    colorSelector->addItems({"Red", "Green", "Blue"});
    colorSelector->setCurrentIndex(0);

    verticalLayout->addWidget(colorSelector);
    verticalLayout->addStretch();

    mainLayout->addLayout(verticalLayout);

    int imageWidth = image.width();
    int imageHeight = image.height();

    for (int yIndex = 0; yIndex < imageHeight; ++yIndex) {
        for (int xIndex = 0; xIndex < imageWidth; ++xIndex) {
            ++colors[image.pixel(xIndex, yIndex) & 0xffffff];
        }
    }

    for (int redRgb = 0; redRgb < 256; ++redRgb) {
        QPixmap slice = QPixmap(256, 256);
        QPainter painter(&slice);

        for (int greenRgb = 0; greenRgb < 256; ++greenRgb) {
            for (int blueRgb = 0; blueRgb < 256; ++blueRgb) {
                if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] > 0) {
                    if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 15)
                        painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 55));
                    else if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 50)
                        painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 155));
                    else painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 255));
                } else {
                    painter.fillRect(greenRgb, blueRgb, 1, 1, QColorConstants::White);
                }
            }
        }
        slices[redRgb] = slice;
    }

    lbl->setPixmap(slices[0]);

}

void ColorHistogram::updateLabelValue(int value) {
    sliderLabel->setText(QString("Slider value: %1").arg(value));
}

void ColorHistogram::updatePixmap(int value) {
    lbl->setPixmap(slices[value]);
}

void ColorHistogram::updateBoxColor(int index) {
    if (index == 0) {
        for (int redRgb = 0; redRgb < 256; ++redRgb) {
            QPixmap slice = QPixmap(256, 256);
            QPainter painter(&slice);

            for (int greenRgb = 0; greenRgb < 256; ++greenRgb) {
                for (int blueRgb = 0; blueRgb < 256; ++blueRgb) {
                    if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] > 0) {
                        if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 15)
                            painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 55));
                        else if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 50)
                            painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 155));
                        else painter.fillRect(greenRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 255));
                    } else {
                        painter.fillRect(greenRgb, blueRgb, 1, 1, QColorConstants::White);
                    }
                }
            }
            slices[redRgb] = slice;
        }
        slider->setValue(0);
        lbl->setPixmap(slices[0]);
        sliderLabel->setText("Slider value: 0");
        xLabel->setText("x-axis: Blue");
        yLabel->setText("y-axis: Green");
    }
    else if (index == 1) {
        for (int greenRgb = 0; greenRgb < 256; ++greenRgb) {
            QPixmap slice = QPixmap(256, 256);
            QPainter painter(&slice);

            for (int redRgb = 0; redRgb < 256; ++redRgb) {
                for (int blueRgb = 0; blueRgb < 256; ++blueRgb) {
                    if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] > 0) {
                        if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 15)
                            painter.fillRect(redRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 55));
                        else if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 50)
                            painter.fillRect(redRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 155));
                        else painter.fillRect(redRgb, blueRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 255));
                    } else {
                        painter.fillRect(redRgb, blueRgb, 1, 1, QColorConstants::White);
                    }
                }
            }
            slices[greenRgb] = slice;
        }
        slider->setValue(0);
        lbl->setPixmap(slices[0]);
        sliderLabel->setText("Slider value: 0");
        xLabel->setText("x-axis: Blue");
        yLabel->setText("y-axis: Red");
    }
    else if (index == 2) {
        for (int blueRgb = 0; blueRgb < 256; ++blueRgb) {
            QPixmap slice = QPixmap(256, 256);
            QPainter painter(&slice);

            for (int redRgb = 0; redRgb < 256; ++redRgb) {
                for (int greenRgb = 0; greenRgb < 256; ++greenRgb) {
                    if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] > 0) {
                        if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 15)
                            painter.fillRect(redRgb, greenRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 55));
                        else if (colors[qRgb(redRgb, greenRgb, blueRgb) & 0xffffff] < 50)
                            painter.fillRect(redRgb, greenRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 155));
                        else painter.fillRect(redRgb, greenRgb, 1, 1, QColor(redRgb, greenRgb, blueRgb, 255));
                    } else {
                        painter.fillRect(redRgb, greenRgb, 1, 1, QColorConstants::White);
                    }
                }
            }
            slices[blueRgb] = slice;
        }
        slider->setValue(0);
        lbl->setPixmap(slices[0]);
        sliderLabel->setText("Slider value: 0");
        xLabel->setText("x-axis: Green");
        yLabel->setText("y-axis: Red");
    }
}
