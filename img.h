#ifndef IMG_H
#define IMG_H
#include <QSize>
#include <QPixmap>
#include <QImage>

//Класс хранит все параметры изображения и само изображение
//Реализованы методы удобного получения/установки параметров, рендеры и тд
//Также класс хранит копию оригинального изображения

class Img
{
public:
    Img(const QString pathStr);
    QImage original
    ;
    int getW() const;
    int getH() const;

    QImage getOriginal() const;
    QImage *getImg() const;
    QPixmap getPixmap() const;
    QString getPath() const;

private:
    QString path;
    QImage* img;
    QPixmap pixmap;
    int w;
    int h;

    void setPath(const QString &pathStr);
        void updatePixmap();
    void setW();
    void setH();
};

#endif // IMG_H
