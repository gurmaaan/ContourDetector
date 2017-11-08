#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ContourDetector");
    showImage(getImagePath());
    imgSize = getImageSize(&originalImg);
    BandWImgDevide3 = convertBandWDevide3(originalImg);
    BandWImgFormula = convertBandWFormula(originalImg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //TODO: Picture resizing
//    QMainWindow::resizeEvent(event);
//    ui->imageLabel->setPixmap(pic);
}

void MainWindow::on_pathButton_clicked()
{
    showImage(getImagePath());
}

QString MainWindow::getImagePath()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Select one or more files to open",
                "C:/Users/Dima/OneDrive/EDUCATION/Research/Molchanov/primery_izobrazheniy_dlya_UIR/",
                "Images (*.png *.xpm *.bmp)");
    return path;
}

void MainWindow::showImage(QString path)
{
    QImage image(path);
    originalImg = image;
    ui->pathLineEdit->setText(path);
    ui->imageLabel->setPixmap(QPixmap::fromImage(originalImg));
}

void MainWindow::updateImage(QImage *img)
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
}

QImage MainWindow::convertBandWDevide3(QImage img)
{
    for (int i=0; i < imgSize.width(); i++)
    {
       for (int j=0; j < imgSize.height(); j++)
       {
           QRgb color = img.pixel(i, j);
           int gray = (qRed(color) + qGreen(color) + qBlue(color))/3;
           img.setPixel(i, j, qRgb(gray, gray, gray));
       }
    }
    return img;
}

QImage MainWindow::convertBandWFormula(QImage img)
{
    for (int i=0; i < imgSize.width(); i++)
    {
       for (int j=0; j < imgSize.height(); j++)
       {
           QRgb color = img.pixel(i, j);
           int gray = getBrightness(qRed(color), qGreen(color), qBlue(color));
           img.setPixel(i, j, qRgb(gray, gray, gray));
       }
    }
    return img;
}

void MainWindow::setTreshold(QImage img, int devisionVal)
{
    ui->bawFormulaRadio->setChecked(true);
    ui->bawDevide3Radio->setChecked(false);
    ui->colorRadio->setChecked(false);

    for(int i = 0; i < imgSize.width(); i++)
    {
        for(int j = 0; j < imgSize.height(); j++)
        {
            QRgb color = img.pixel(i, j);
            int brightness = getBrightness(qRed(color), qGreen(color), qBlue(color));

            if (brightness >= devisionVal)
                img.setPixel(i, j, qRgb(255, 255, 255));
            else
                img.setPixel(i, j, qRgb(0, 0, 0));
        }
    }
    updateImage(&img);
}

void MainWindow::on_trashholSlider_sliderMoved(int position)
{
    ui->devesaionSpinBox->setValue(position);
   setTreshold(BandWImgFormula, position);
}

void MainWindow::on_colorRadio_clicked()
{
    updateImage(&originalImg);
}

void MainWindow::on_bawDevide3Radio_clicked()
{
    updateImage(&BandWImgDevide3);
}

void MainWindow::on_bawFormulaRadio_clicked()
{
    updateImage(&BandWImgFormula);
}

int MainWindow::getBrightness(int red, int green, int blue)
{
    return red * RED_COEF + green * GREEN_COEF + blue * BLUE_COEF;
}
