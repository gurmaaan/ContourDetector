#ifndef CNST_H
#define CNST_H

//Коэфициент размера окна программы относительно размер экрана
#define SCREEN_SCALE 0.75

//Коэффициент растяжения по умолчанию //=1, не растянуто
#define ZOOM_SCALE 1

//Значение порога бинаризации по умолчанию
#define DEFAULT_TRESHOLD 100

//Цвета для функции получения яркости
#define RGB_BLACK qRgb(0,0,0)
#define RGB_WHITE qRgb(255, 255, 255)
#define RGB_RED qRgb(255, 0, 0)

//Фильтры типа файлов
#define TYPE_FILTER_BMP "Bitmap Image (*.bmp)"
#define TYPE_FILTER_PNG "PNG Images (*.png)"
#define TYPE_FILTER_JPG "JPG Images (*.jpg)"
#define TYPE_FILTER_TIF "TIF Images (*.tif)"

//Фильтры суффикса
#define SUFFIX_FILTER_BMP "bmp"
#define SUFFIX_FILTER_PNG "png"
#define SUFFIX_FILTER_JPG "jpg"
#define SUFFIX_FILTER_TIF "tif"

//Стиль кнопки колорпикера
#define CLR_PCKR_STYLE "border: 1px solid black; background-color: "

//Диалоговые окна:
    // Сообщения
#define OPEN_FAILED "Не могу загрузить изображение %1: %2"
#define OPEN_SUCCESS "Открыто изображение \"%1\", %2x%3, Depth: %4"
#define SAVE_FAILED "Не могу сохранить изображение %1: %2"
#define SAVED_SUCCESS "Сохранено изображение \"%1\" "

    //Заголовки
#define OPEN_NORMAL "Выберите файл"

    //Путь
// WARNING:: Chenge before Proni
#define OPEN_PATH_DEFAULT "%HOMEPATH%YandexDisk/EDUCATION/Research/Molchanov/ContourDetector/TestImages/"

#include <QObject>
#include <QMetaClassInfo>

    //Время отображения сообщения в статус баре
#define TIMEOUT 500

class Cnst : public QObject
{
    Q_OBJECT
public:
    explicit Cnst(QObject *parent = nullptr);

    enum SuccessMessage
    {
        ImgOpened,
        ImgSaved
    };

    enum ErrorMessage
    {
        ImgOpenFailed,
        ImgSaveFailed
    };

    enum DialogTitle
    {
        SelectImg
    };

    enum ImgType
    {
        BmpFilter,
        PngFilter,
        JpgFilter,
        TifFilter,

        BmpSuffix,
        PngSuffix,
        JpgSuffix,
        TifSuffix
    };

    enum RgbClr
    {
        Black,
        White,
        Red
    };

    enum Scale
    {
        Screen,
        Zoom
    };

    enum ColorFactor
    {
        RedF,
        GreenF,
        BlueF
    };

    const double factor(ColorFactor clr);
    static const double scaling(Scale mode);

    static const QString errorMessageText(ErrorMessage type);
    static const QString img(ImgType type);

signals:
    void pushMessage(const QString mes);

public slots:
    void showMessage(const QString command);
};

#endif // CNST_H
