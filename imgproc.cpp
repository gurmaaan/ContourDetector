#include "imgproc.h"

ImgProc::ImgProc(const QImage &image)
{

    loadImage(image);
}

ImgProc::ImgProc()
{

}

//TODO: (Общее) сделать нормальную нотификацию в статус бар
void ImgProc::loadImage(const QImage &image)
{
    _loaded = !image.isNull();
    if ( _loaded )
    {
        //_img = image;
        _sizeValid = calculateSize(image);
        if (_sizeValid) {
            _colorSaved = saveClrImgCopy(image);
            if (_colorSaved) {
                _bwConverted = convertToBw(image);
                if (_bwConverted) {
                    calculateAutoTrBarrier();
                    if (_trAutoValCalculated) {
                        setImgTr(image);
                        _trConverted = genBitTrArray(_autoTr);
                        if(_trConverted) {
                            qDebug() << "Image succesfully proccesed";
                        }
                    }
                }
            }
        }
    }
    else {
        qCritical() << "Couldn't load image : file doesn't exist or has incorrect type";
    }
    _autoTr = calculateTrVal(image);
    _trcalculated = convertToTr(_autoTr);
}

QImage ImgProc::getImgClr() const
{
    return _imgClr;
}

bool ImgProc::saveClrImgCopy(const QImage &originalImg)
{
    _imgClr = originalImg;
    if (!_imgClr.isNull()) {
        qInfo() << "Colored copy saved.";
        return true;
    } else
        qCritical() << "Couldn't save colored copy of original image : original image return null";
        return false;
}

int ImgProc::getAutoTrBarrier() const
{
    return _autoTr;
}

QImage *ImgProc::getImgBw() const
{
    return _imgBw;
}

void ImgProc::setImgBw(QImage *imgBw)
{
    _imgBw = imgBw;
}

QImage *ImgProc::getImgTr() const
{
    return _imgTr;
}

void ImgProc::setImgTr(QImage *imgTr)
{
    _imgTr = imgTr;
}

bool ImgProc::calculateSize(QImage *image)
{
    int tempw = image->size().width();
    int temph = image->size().height();

    if (tempw > 0 && temph > 0)
    {
        _w = tempw;
        _h = temph;
        qInfo() << "\nImage size :\n\twidth = " << _w << "\n\theight = " << _h;
        return true;
    }
    else
    {
        _w = 0, _h = 0;
        qCritical() << "Incorrect image size:\n\tw = " << tempw << "\n\th = " << temph;
        return false;
    }
}

bool ImgProc::convertToBw(QImage *image)
{
    _imgBw = image;

    QTime t1 = QTime::currentTime();

    if ( !_imgBw->isNull() )
    {
        for (int i = 0; i < _w; i++)
        {
            for (int j = 0; j < _h; j++)
            {
                int gray = qGray( image->pixel(i, j) );
                if (!(gray < 0 || gray > 255))
                {
                    _brightnessMap.push_back( (unsigned char*)gray );
                    _imgBw->setPixel(i, j, qRgb(gray, gray, gray));
                }
                else {
                    qCritical() << "Error brightness value at pixel (" << i <<" , " << j << ") : " << gray;
                    break;
                    return false;
                }

            }
        }

        QTime t2 = QTime::currentTime();
        int delta = t2.msec() - t1.msec();
        qInfo() << "Converted to BW in " << delta << " msec.";
        return true;
    } else
    {
        qCritical() <<"Doesn't convert to BW : original image return null.";
        return false;
    }
    //В ЧБ копию изображения скопировали оригинальное (ЧБ = ориг)
    setImgBw(image);
}

//Функция принимает пиксель и возвращает значение яркости этого пикселя рассчитанного по формуле из Гонсалеса
int ImgProc::getPixelBrightness(QRgb pixel)
{
    int ownGray = qRed(pixel)*RED_RATIO + qGreen(pixel)*GREEN_RATIO + qBlue(pixel)*BLUE_RATIO;
    int qtGray = qGray(pixel);
    qDebug() << "Own GrayScale : " << ownGray << "Qt GrayScale : " << qtGray;
    return ownGray;
}


//Рассчитывает значение порога бинаризации по средней ярркости пикселя
int ImgProc::calculateAutoTrBarrier()
{
    long int brightSum = 0;
    long int pixelsAmount = _w * _h;

    if (pixelsAmount == 0)
    {
        qCritical() << "Image with no pixels received.";
    }
    else
    {
        QTime t1 = QTime::currentTime();

        for (int i = 0; i < _w; ++i) {
            for (int j = 0; j < _h; ++j) {
                brightSum += _brightnessMap.at(i)[j];
            }
        }

        QTime t2 = QTime:: currentTime();
        int delta = t2.msec() - t1.msec();

        _autoTr = brightSum / pixelsAmount;

        if (_autoTr > 0 )
        {
            _trAutoValCalculated = true;
            _tr = _autoTr;

            qInfo() << "Threshold value calculate automathic in " << delta << " msec.";
            qInfo() << "\tPixels amount : " << pixelsAmount;
            qInfo() << "\tTotal brightness : " << brightSum;
            qInfo() << "\tCalculated threshold barrier : " << _autoTr;

        }
        else
        {
            qCritical() << "Error via calculating threshold barrier : calculated value is negative";
            _trAutoValCalculated = false;
            _autoTr = 0;
            _tr = 0;
       }
    }
    return _autoTr;
}

//Генерация бинарного изображения исходя из порога бинаризации
bool ImgProc::genBitTrArray(int barrier)
{
    if ( (_brightnessMap.size() == _w * _h) && (!_imgTr.isNull()))
    {
        QTime t1 = QTime::currentTime();

        for (int i = 0; i < _w; i++)
        {
            for (int j = 0; j < _h; j++)
            {
                int pixelBrightness = _brightnessMap.at(i)[j];
                bool bit = pixelBrightness <= barrier ? true : false;
               _imgBin.at(i).push_back(bit);

                const QColor pixClr = bit ? Qt::black : Qt ::white;
                _imgTr.setPixelColor(i, j, pixClr);
            }
        }
        QTime t2 = QTime::currentTime();
        int delta = t2.msec() - t1.msec();
        qInfo() << "Module bitmap calculation done in " << delta << " msec.";
        return true;
    } else
    {
        qCritical() << "Error while threshold calculation : incorrect brightness map size - " << _brightnessMap.size();
        return false;
    }

}


//TODO : Нормальный трешхолд и распознавание контуров
