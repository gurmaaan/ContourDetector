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

    bool    _loaded         = false;
    bool    _bwconverted    = false;
    bool    _trcalculated   = false;

    int _w = 0;
    int _h = 0;

    void loadImage(const QImage &image);

    QImage getImgClr() const;
    void setImgClr(const QImage &value);

    QImage getImgBw() const;
    void setImgBw(const QImage &value);

    QVector<QVector<bool>> mask;
    int getAutoTr() const;

    QImage getImgTr(int lavel);
    void setImgTr(const QImage &value);

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

    int calculateTrVal(const QImage &image);
    bool convertToTr(int val);
};

#endif // IMGPROC_H
;
