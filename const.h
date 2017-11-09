#ifndef CONST_H
    #define CONST_H

#include <QDebug>
    //Константы формулы яркости I = 0,2125R + 0,7154G + 0,0721B
    #define RED_RATIO 0.2125
    #define GREEN_RATIO 0.7154
    #define BLUE_RATIO 0.0721
    namespace ColorCoeff {
        double R = RED_RATIO,
           G = GREEN_RATIO,
           B = BLUE_RATIO;
    }

    //Цвета для функции получения яркости
    #define RGB_BLACK qRgb(0,0,0)
    #define RGB_WHITE qRgb(255, 255, 255)
    namespace RgbColor {
        QRgb black = RGB_BLACK,
             white = RGB_WHITE;
    }

    //Общие константы
    #define CHOSE_TITTLE "Выберите картинку"
    #define CHOSE_FILTER_BMP "Bitmap Image (*.bmp)"
    #define CHOSE_FILTER_PNG "PNG Images (*.png)"
    #define CHOSE_FILTER_JPG "JPG Images (*.jpg)"
    #define CHOSE_FILTER_TIF "TIF Images (*.tif)"
    #define CHOSE_PATH "C:/Users/Dima/OneDrive/EDUCATION/Research/Molchanov/ContourDetector/TestImages/"

    //Изображение
    #define CLR_PCKR_STYLE "border: 1px solid black; background-color: "
#endif // CONST_H