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
#include <QBitArray>
#include <QTime>

class ImgProc
{
public:
    ImgProc(const QImage &image);
    ImgProc();

    //TODO : добавить изменение Opacity

    //Индикаторы статуса
    bool _loaded                 = false;
    bool _sizeValid              = false;
    bool _colorSaved             = false;
    bool _bwConverted            = false;
    bool _trAutoValCalculated    = false;
    bool _trConverted            = false;

    int _w = 0;
    int _h = 0;

    void loadImage(const QImage &image);

    QImage getImgClr() const;
    bool saveClrImgCopy(const QImage &originalImg);

    int getAutoTrBarrier() const;
    bool genBitTrArray(int barrier);

    QImage *getImgBw() const;
    void setImgBw(QImage *imgBw);

    QImage *getImgTr() const;
    void setImgTr(QImage *imgTr);

signals:
    void sendStatus(const QString);

private:
    QImage  *_img; //основное (исходное) изображение с которым постоянно работаем и его же обрабатываем

    QImage  *_imgClr;// Цветная копия
    QImage *_imgBw; // Чернобелая копия
    QImage *_imgTr; //После создания массива бит

    QVector<unsigned __int8*> _brightnessMap;
    QVector<bool*> _imgBin; //Дубликат основного изображения со значениями яркостей 0 или 1

    int _autoTr = 0; //автомиатически высчитанный порог бинаризации
    int _tr = 0; //текущее значение уровня бинаризации

    //NOTE : не логично, лучше бы она возвращала QSize
    bool calculateSize(QImage *image);

    //NOTE : проверить в сравнение с qGray че будет пше
    int getPixelBrightness(QRgb pixel);

    bool convertToBw(QImage *image);
    int calculateAutoTrBarrier();

};

#endif // IMGPROC_H
;
