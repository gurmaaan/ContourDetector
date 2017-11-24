#ifndef IMGPROC_H
#define IMGPROC_H

//Константы формулы яркости I = 0,2125R + 0,7154G + 0,0721B
//Следубют из кривой видности
#define RED_RATIO 0.2125
#define GREEN_RATIO 0.7154
#define BLUE_RATIO 0.0721

#include <QImage>
#include <QDebug>
#include <QPixmap>

class ImgProc
{
public:
    ImgProc(const QImage &image);
    ImgProc();

    bool    loaded = false,
            bwconverted = false,
            trcalculated = false;
    int w = 0,
        h = 0;
    void loadImage(const QImage &image);

    QImage getImgClr() const;
    void setImgClr(const QImage &value);

    QImage getImgBw() const;
    void setImgBw(const QImage &value);

    int getAutoTr() const;

private:
    QImage  *img; //изображение с которым постоянно работаем и его же обрабатываем

    QImage  imgClr, //цветная копия исходного
            imgBw, //чернобелая копию
            imgTr; //изображение после трешолда
    int autoTr = 0, //значение порога бинаризации рассчитанное автоматически
        tr = 0; //текущее значение уровня бинаризации

    bool calculateSize(const QImage &image);
    void convertToBw(const QImage &image);
    int getPixelBrightness(QRgb pixel);
    int calculateTr(const QImage &image);
};

#endif // IMGPROC_H
