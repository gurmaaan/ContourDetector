#include "cnst.h"

Cnst::Cnst(QObject *parent) : QObject(parent)
{

}

void Cnst::showMessage(const QString command)
{
    QMetaObject MetaObject = this->staticMetaObject;
    QMetaEnum MetaEnum = MetaObject.enumerator(MetaObject.indexOfEnumerator("StatusMessages"));

    switch ( MetaEnum.keysToValue(command.toLatin1()) ) {
    case ImgOpened:
        emit pushMessage(OPEN_SUCCESS);
        break;
    case ImgSaved:
        emit pushMessage(SAVED_SUCCESS);
        break;

    default:
        emit pushMessage("Готов");
        break;
    }
}

const QString Cnst::errorMessageText(Cnst::ErrorMessage type)
{
    switch (type) {
    case ErrorMessage::ImgOpenFailed:
        return OPEN_FAILED;
        break;
    case ErrorMessage::ImgSaveFailed:
        return SAVE_FAILED;
    default:
        return "1";
        break;
    }
}


//TODO оставшиеся 3 типа (но мб и не надо проверить новую фичу Qt 5.9)
const QString Cnst::img(ImgType type)
{
    switch (type) {
    case ImgType::BmpFilter:
        return TYPE_FILTER_BMP;
        break;

    case ImgType::BmpSuffix:
        return SUFFIX_FILTER_BMP;
        break;

    default:
        break;
    }
}

const double Cnst::scaling(Scale mode)
{
    switch (mode) {
    case Scale::Screen:
        return SCREEN_SCALE;
        break;
    case Scale::Zoom:
        return ZOOM_SCALE;
    default:
        return 1;
        break;
    }

}


