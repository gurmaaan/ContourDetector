#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "const.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //BUG: Resizing without Saving Aspect Ratio
    ui->setupUi(this);
    showImage(getImagePath());

    imgSize = getImageSize(&originalImg);
    bwImg = setBW(originalImg);
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
    //WARNING: Change path to Pictures directory before Proni4ev review
    QString path = QFileDialog::getOpenFileName(
                this,
                CHOSE_TITTLE,
                CHOSE_PATH,
                CHOSE_FILE_EXT);
    return path;
}

void MainWindow::showImage(QString path)
{
    QImage image(path);
    originalImg = image;
    ui->pathLineEdit->setText(path);
    updateImage(&image);
}

void MainWindow::updateImage(QImage *img)
{
    *img = img->scaledToWidth(ui->imageLabel->size().width());
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
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
   updateImage(&tresholdedImg);
}

void MainWindow::on_colorRadio_clicked()
{
    updateImage(&originalImg);
}

int MainWindow::getBrightness(QRgb pixel)
{

    int brightness =
            qRed(pixel) * (ColorCoeff::R) +
            qGreen(pixel)* (ColorCoeff::G) +
            qBlue(pixel) * (ColorCoeff::B);
    return brightness;
}

QVector<QPoint> MainWindow::findContour(QImage img)
{

}

QImage MainWindow::paintContour(QVector<QPoint> points)
{

}

void MainWindow::on_tresholdRatio_clicked()
{
    updateImage(&tresholdedImg);
}


void MainWindow::on_findContourButton_clicked()
{

}

void MainWindow::on_colorPeakerButton_clicked()
{
    QColor contourClr = QColorDialog::getColor(Qt::red, this);
    QString bgStyleSheet = CLR_PCKR_STYLE + contourClr.name();
    ui->colorPeakerButton->setStyleSheet(bgStyleSheet);
}

void MainWindow::on_bwRatio_clicked()
{
    updateImage(&bwImg);
}
