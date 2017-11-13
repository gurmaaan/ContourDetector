#ifndef CONST_H
#define CONST_H

#include <QString>
#include <QRgb>

    //Константы формулы яркости I = 0,2125R + 0,7154G + 0,0721B
    #define RED_RATIO 0.2125
    #define GREEN_RATIO 0.7154
    #define BLUE_RATIO 0.0721

    //Значение порога бинаризации по умолчанию
    #define DEFAULT_TRESHOLD 1

    //Цвета для функции получения яркости
    #define RGB_BLACK qRgb(0,0,0)
    #define RGB_WHITE qRgb(255, 255, 255)
    #define RGB_RED qRgb(255, 0, 0)

    //Обработчик файлов
    #define CHOSE_TITTLE "Выберите картинку"
    #define CHOSE_PATH "C:/Users/Dima/OneDrive/EDUCATION/Research/Molchanov/ContourDetector/TestImages/"

    //Фильтры типа файлов
    #define TYPE_FILTER_BMP "Bitmap Image (*.bmp)"
    #define TYPE_FILTER_PNG "PNG Images (*.png)"
    #define TYPE_FILTER_JPG "JPG Images (*.jpg)"
    #define TYPE_FILTER_TIF "TIF Images (*.tif)"

    //Изображение
    #define CLR_PCKR_STYLE "border: 1px solid black; background-color: "

namespace ColorCoeff {
    double  R = RED_RATIO,
            G = GREEN_RATIO,
            B = BLUE_RATIO;
}

namespace RgbColor {
    QRgb black = RGB_BLACK,
         white = RGB_WHITE,
         red = RGB_RED;
}

namespace ImgFileType {
    const QString   BMP(TYPE_FILTER_BMP),
                    JPG(TYPE_FILTER_JPG),
                    PNG(TYPE_FILTER_PNG),
                    TIF(TYPE_FILTER_TIF),
                    ALL = BMP + ";;" + JPG + ";;" + PNG + ";;" + TIF;
}
#endif // CONST_H
