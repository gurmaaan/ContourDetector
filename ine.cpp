for (int j = 0; j < _h; j++) 
{
    QRgb *line = (QRgb *)imgTr.scanLine(j);
    brigntMap.push_back( line );
}

QImage ImgProc::getImgTr(int lavel)
{
    if (_bwConverted ) convertToTr(lavel);
    return _imgTr;
}

void ImgProc::setImgTr(const QImage &value)
{
    _imgTr = value;
}

QImage getImgTr(int lavel);
void setImgTr(const QImage &value);

bool ImgProc::convertToTr(int val)
{
    _tr = val;
    QVector<QRgb*> brigntMap;
    //setImgTr(_imgBw);

    if (_loaded && _bwConverted)
    {

    } else
        return false;

    for (int j = 0 ; j < _h ; j ++)
    {
        for (int i = 0; i < _w; i++)
        {
            const QColor clr = ( qGray(brigntMap.at(j)[i]) == val ) ? Qt::black : Qt ::white;
            _imgTr.setPixelColor(i, j, clr);
        }
    }
    return true;
}
