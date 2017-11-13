#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QColorDialog>
#include <QStandardPaths>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include "const.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //BUG: Resizing without Saving Aspect Ratio
    ui->setupUi(this);
    showImage(getImagePath());

    imgSize = getImageSize(&originalImg);

    bwImg = setBW(originalImg);
    tresholdedImg = setTreshold(originalImg, DEFAULT_TRESHOLD);
    contourClr = QColor(RGB_RED);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::savePicture(const QString name)
{
    //TODO: Save Picture
    QString fullPath = QDir::tempPath() + name;
    QFile file(fullPath);
    file.open(QIODevice::WriteOnly);
    //ui->imageLabel->pixmap().save(&file, "PNG");
}

void MainWindow::on_pathButton_clicked()
{
    showImage(getImagePath());
}

QString MainWindow::getImagePath()
{
    return QFileDialog::getOpenFileName(this,
                                      CHOSE_TITTLE,
                                      CHOSE_PATH,
                                      ImgFileType::ALL);
}

void MainWindow::showImage(QString path)
{
    QImage image(path);
    originalImg = image;
    ui->pathLineEdit->setText(path);
    updateImage(&image, false);
}

void MainWindow::updateImage(QImage *img, bool withContour)
{
    *img = img->scaledToWidth(ui->imageLabel->size().width());
    //imgSize = getImageSize(img);

    if (!withContour)
        ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
    else
    {
      //  QVector<QPoint> vec = ;
//        ui->imageLabel->setPixmap( QPixmap::fromImage(mergedImage( img , )));
      //  ui->imageLabel->setPixmap(QPixmap::fromImage(*paintContour( findContour(img), contourClr, ui->contourSizeSpin->value() )));
        findContour(img);
    }
}

QImage MainWindow::setBW(QImage img)
{
    for (int i=0; i < imgSize.width(); i++)
    {
       for (int j=0; j < imgSize.height(); j++)
       {
           QRgb color = img.pixel(i, j);
           int gray = getBrightness(color);
           img.setPixel(i, j, qRgb(gray, gray, gray));
       }
    }
    return img;
}

QImage MainWindow::setTreshold(QImage img, int devisionVal)
{
    bool treshold = true;
    ui->colorRadio->setChecked(!treshold);
    ui->bwRatio->setChecked(!treshold);
    ui->tresholdRatio->setChecked(treshold);

    for(int i = 0; i < imgSize.width(); i++)
    {
        for(int j = 0; j < imgSize.height(); j++)
        {
            QRgb color = img.pixel(i, j);
            int brightness = getBrightness(color);

            if (brightness >= devisionVal)
                img.setPixel(i, j, RgbColor::white);
            else
                img.setPixel(i, j, RgbColor::black);
        }
    }
    return img;
}

void MainWindow::on_trashholSlider_sliderMoved(int position)
{
   ui->devesaionSpinBox->setValue(position);
   tresholdedImg = setTreshold(bwImg, position);
   updateImage(&tresholdedImg, ui->contourCheckBox->isChecked());
}

void MainWindow::on_colorRadio_clicked()
{
    updateImage(&originalImg, false);
}

void MainWindow::on_tresholdRatio_clicked()
{
    updateImage(&tresholdedImg, ui->contourCheckBox->isChecked());
}


int MainWindow::getBrightness(QRgb pixel)
{

    int brightness =
            qRed(pixel) * (ColorCoeff::R) +
            qGreen(pixel)* (ColorCoeff::G) +
            qBlue(pixel) * (ColorCoeff::B);
    return brightness;
}

QVector<QPoint> MainWindow::findContour(QImage *img)
{
    int count = 0;
    QVector<QPoint> contPoints;
    for (int i = 1; i < img->size().width() - 1; i++)
    {
        for (int j = 1; j < img->size().height() - 1; j ++)
        {
            QRgb pixel = img->pixel(i, j);
            if ( getBrightness(pixel) == 0) //the pixel is black
            {
                int n = i-1, m = j;
                if (!( getBrightness(img->pixel(n, m)) == 0 )) //хотя бы один пиксель из рамки белый = > контур
                {
                    contPoints.push_back(QPoint(i, j));
                    qDebug() << count++ << " : " << " x = " << i << "y = " << j << " ; " << " n = " << n << " m = " << m;
                    QImage *coverImg = new QImage(img->size(), QImage::Format_ARGB32);
                    coverImg->fill(Qt::transparent);

                    QPainter painter(coverImg);
                    painter.setPen(QPen(Qt::red, ui->contourSizeSpin->value(), Qt::SolidLine, Qt::SquareCap));
                    painter.drawPoint(i, j);
                    painter.end();
                    updateImage(coverImg, true);
                    break;
                }
            }


        }
    }
}

QImage *MainWindow::paintContour(QVector<QPoint> points, const QColor color, const int width)
{
    QImage *coverImg = new QImage(imgSize, QImage::Format_ARGB32);
    coverImg->fill(Qt::transparent);

    QPainter painter(coverImg);
    painter.setPen(QPen(color, width, Qt::SolidLine, Qt::SquareCap));

    for (int i = 0; i < (int)points.length(); i ++)
        painter.drawPoint(points.at(i));

    painter.end();

    return coverImg;
}

QImage MainWindow::mergedImage(QImage *baseImg, QImage *overlayImg)
{
    QImage imageWithOverlay = QImage(getImageSize(baseImg), QImage::Format_ARGB32);
    QPainter painter(&imageWithOverlay);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, *baseImg);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, *overlayImg);

    painter.end();

    return imageWithOverlay;
}

void MainWindow::on_colorPeakerButton_clicked()
{
    contourClr = QColorDialog::getColor(Qt::red, this);
    QString bgStyleSheet = CLR_PCKR_STYLE + contourClr.name();
    ui->colorPeakerButton->setStyleSheet(bgStyleSheet);
}

void MainWindow::on_bwRatio_clicked()
{
    updateImage(&bwImg, false);
}

void MainWindow::on_contourCheckBox_clicked()
{
    findContour(&tresholdedImg);
}
