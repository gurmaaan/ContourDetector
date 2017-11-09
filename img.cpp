#include "img.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

Img::Img(const QString pathStr)
{
    setPath(pathStr);
    img = new QImage(path);
    original = *img;
    setW();
    setH();
    updatePixmap();
}

int Img::getW() const
{
    return w;
}

int Img::getH() const
{
    return h;
}

QPixmap Img::getPixmap() const
{
    return pixmap;
}

QImage Img::getOriginal() const
{
    return original;
}

QImage *Img::getImg() const
{
    return img;
}

QString Img::getPath() const
{
    return path;
}

void Img::updatePixmap()
{
    pixmap = QPixmap::fromImage(*img);
}

void Img::setW()
{
    if ( img->size().width() != 0)
        w = img->size().width();
}

void Img::setH()
{
    if ( img->size().height() != 0)
        h = img->size().height();
}

void Img::setPath(const QString &pathStr)
{
    QFileInfo checkPath(pathStr);
    if(checkPath.exists() && checkPath.isFile()) {
        path = pathStr;
    } else {
        QMessageBox::critical(0, "Error", "An error has occured with image file path");
        qDebug() << "Img class, setPath(), pathStr = " << pathStr;
    }
}



