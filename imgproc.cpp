#include "imgproc.h"
#include <QPixmap>

ImgProc::ImgProc(const QImage &image)
{
    loadImage(image);
}

ImgProc::ImgProc()
{

}

void ImgProc::loadImage(const QImage &image)
{
    loaded = !image.isNull();
    if ( loaded ) {
        setImgClr(image);
        qInfo() << "Color copy : done";
    } else {
        qCritical() << "Couldn't load image : object you set return null";
    }
    calculateSize(image);
    convertToBw(image);
    if ( bwconverted ) {
        qInfo() << "BW copy : done";
    }

    autoTr = calculateTr(image);
}

QImage ImgProc::getImgClr() const
{
    return imgClr;
}

void ImgProc::setImgClr(const QImage &value)
{
    imgClr = value;
}

QImage ImgProc::getImgBw() const
{
    return imgBw;
}

void ImgProc::setImgBw(const QImage &value)
{
    imgBw = value;
}

int ImgProc::getAutoTr() const
{
    return autoTr;
}

//bool ImgProc::calculateTr(QImage image)
//{

//}

bool ImgProc::calculateSize(const QImage &image)
{
    if ( loaded ) {
        w = image.size().width();
        h = image.size().height();
        qInfo() << "\nImage size :\n\twidth - " << w << "\n\theight - " << h;
        return true;
    }
    else {
        w = 0, h = 0;
        qCritical() << "Couldn't calculate image size : image wasn't load";
        return false;
    }
}

void ImgProc::convertToBw(const QImage &image)
{
    setImgBw(image);
    if ( loaded )
    {
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                int gray = getPixelBrightness( image.pixel(i, j) );
                imgBw.setPixel(i, j, qRgb(gray, gray, gray));
            }
        }
        bwconverted = true;
    } else
    {
        qDebug() <<"Doesn't convert to BW : image not loaded";
        bwconverted = false;
    }
}

int ImgProc::getPixelBrightness(QRgb pixel)
{
    return qRed(pixel)*RED_RATIO + qGreen(pixel)*GREEN_RATIO + qBlue(pixel)*BLUE_RATIO;
}

int ImgProc::calculateTr(const QImage &image)
{
    long int brightSum = 0;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            brightSum += getPixelBrightness( image.pixel(i, j) );
        }
    }

    return brightSum / (w * h);
}
