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
    _loaded = !image.isNull();
    if ( _loaded ) {
        setImgClr(image);
        qInfo() << "Color copy : done";
    } else {
        qCritical() << "Couldn't load image : object you set return null";
    }
    calculateSize(image);
    convertToBw(image);
    if ( _bwconverted ) {
        qInfo() << "BW copy : done";
    }

    autoTr = calculateTrVal(image);
    _trcalculated = convertToTr(autoTr);
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

QImage ImgProc::getImgTr(int lavel)
{
    if (_bwconverted ) convertToTr(lavel);
    return imgTr;
}

void ImgProc::setImgTr(const QImage &value)
{
    imgTr = value;
}

bool ImgProc::calculateSize(const QImage &image)
{
    if ( _loaded ) {
        _w = image.size().width();
        _h = image.size().height();
        qInfo() << "\nImage size :\n\twidth - " << _w << "\n\theight - " << _h;
        return true;
    }
    else {
        _w = 0, _h = 0;
        qCritical() << "Couldn't calculate image size : image wasn't load";
        return false;
    }
}

void ImgProc::convertToBw(const QImage &image)
{
    setImgBw(image);
    if ( _loaded )
    {
        for (int i = 0; i < _w; i++)
        {
            for (int j = 0; j < _h; j++)
            {
                int gray = getPixelBrightness( image.pixel(i, j) );
                imgBw.setPixel(i, j, qRgb(gray, gray, gray));
            }
        }
        _bwconverted = true;
    } else
    {
        qDebug() <<"Doesn't convert to BW : image not loaded";
        _bwconverted = false;
    }
}

int ImgProc::getPixelBrightness(QRgb pixel)
{
    return qRed(pixel)*RED_RATIO + qGreen(pixel)*GREEN_RATIO + qBlue(pixel)*BLUE_RATIO;
}

int ImgProc::calculateTrVal(const QImage &image)
{
    long int brightSum = 0;
    for (int i = 0; i < _w; ++i) {
        for (int j = 0; j < _h; ++j) {
            brightSum += getPixelBrightness( image.pixel(i, j) );
        }
    }

    return brightSum / (_w * _h);
}

bool ImgProc::convertToTr(int val)
{
    tr = val;
    QVector<QRgb*> brigntMap;
    setImgTr(imgBw);

    imgTr = imgBw.convertToFormat(QImage::Format_ARGB32);
    QVector<bool> objectMap;

    if (_loaded && _bwconverted)
    {
        for (int j = 0; j < _h; j++) {
            QRgb *line = (QRgb *)imgTr.scanLine(j);
            brigntMap.push_back( line );
        }
    } else
        return false;

    for (int j = 0 ; j < _h ; j ++) {
        for (int i = 0; i < _w; i++)
        {
            const QColor clr = ( qGray(brigntMap.at(j)[i]) == val ) ? Qt::black : Qt ::white;
            imgTr.setPixelColor(i, j, clr);
        }
    }
    return true;
}
