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

    autoTr = calculateTrVal(imgBw);
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

QImage ImgProc::getImgCt(int lavel)
{
    if (_trconverted ) convertToCt(lavel);
    return imgCt;
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

    //imgTr = imgBw.convertToFormat(QImage::Format_ARGB32);
//    QVector<bool> objectMap;

    if (_loaded && _bwconverted)
    {
        for (int j = 0; j < _h; j++) {
            QRgb *line = (QRgb *)imgTr.scanLine(j);
            brigntMap.push_back( line );
        }
    } else
        return false;

    for (int j = 0 ; j < _h ; j++) {
        for (int i = 0; i < _w; i++)
        {
            const QColor clr = ( qGray(brigntMap.at(j)[i]) < val ) ? Qt::black : Qt ::white;
            imgTr.setPixelColor(i, j, clr);
        }
    }
    _trconverted = true;
    return true;
}

bool ImgProc::convertToCt(int val) {
    imgCt = imgTr;

    val = val * 2 + 1;

    for (int i = 1; i < _h - 1; i++)
    {
        for (int j = 1; j < _w - 1; j++)
        {
            if( getPixelBrightness ( imgTr.pixel(j - 1, i - 1 ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j - 1, i     ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j - 1, i + 1 ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j    , i - 1 ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j    , i + 1 ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j + 1, i - 1 ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j + 1, i     ) ) == 0  &&
                getPixelBrightness ( imgTr.pixel(j + 1, i + 1 ) ) == 0  )
                                     imgCt.setPixelColor(j, i, Qt::white);
        }
    }
    QImage imgCtAdv(imgCt.width(), imgCt.height(), imgCt.format());

    for (int i = 1; i < _h - 1; i++)
    {
        for (int j = 1; j < _w - 1; j++)
        {
            imgCtAdv.setPixelColor(j, i, Qt::white);
        }
    }


    for (int i = val / 2; i < _h - val / 2; i++)
    {
        for (int j = val / 2; j < _w - val / 2; j++)
        {
//            int center = val / 2 + 1;
            int tmp_i=i-2,tmp_j=j-2;
            int min = 255; // Установка максимального значения
            if(getPixelBrightness ( imgCt.pixel(j, i)) == 0) {
                for( int ii = -val/2; ii <= val/2; ++ii)
                    for( int jj = -val/2; jj <= val/2; ++jj)
                       if(ii != 0 && jj != 0) {
                           if (getPixelBrightness(imgBw.pixel(j + jj, i + ii)) < min) // Тут изменить функцию минимума
                           {
                               tmp_i = i + ii;
                               tmp_j = j + jj;
                               min = getPixelBrightness(imgBw.pixel(j + jj, i + ii));
                           }
                       }
                imgCtAdv.setPixelColor(tmp_j, tmp_i, Qt::red);
            }
        }
    }

    int counter = 0;
    for (int i = 1; i < _h - 1; i++)
    {
        for (int j = 1; j < _w - 1; j++)
        {
            int first = getPixelBrightness(imgCt.pixel(j,i));
            int second = getPixelBrightness(imgCtAdv.pixel(j,i));

            if (second  - first != 0)
                counter++;
        }
    }

    qDebug() << counter << _h << _w;

    imgCt = imgCtAdv;

    return true;
}
