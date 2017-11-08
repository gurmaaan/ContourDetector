#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ContourDetector");

    showImage(getImagePath());

    imgSize = getImageSize(&originalImg);
    bwImg = setBW(originalImg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //TODO: Picture resizing
    QMainWindow::resizeEvent(event);
    int w = ui->imageLabel->width();
    int h = ui->imageLabel->height();
    //ui->imageLabel->setPixmap(ui->imageLabel->pixmap()->scaled(w, h, Qt::KeepAspectRatio));

    qDebug() << "Windows width: " << this->width() << "PixMap width: " << ui->imageLabel->pixmap()->size().width() << "Label width: " << ui->imageLabel->width();
    qDebug() << "---------------";
}

void MainWindow::savePicture(QPixmap picture, const QString name)
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
    QString path = QFileDialog::getOpenFileName(
                this,
                "Выберите картинку",
                "C:/Users/Dima/OneDrive/EDUCATION/Research/Molchanov/primery_izobrazheniy_dlya_UIR/",
                "Images (*.png *.xpm *.bmp)");
    return path;
}

void MainWindow::showImage(QString path)
{
    QImage image(path);
    originalImg = image;
    ui->pathLineEdit->setText(path);
   // ui->imageLabel->setGeometry(0,0,image.size().width(),image.size().height());
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
    ui->bawFormulaRadio->setChecked(false);
    ui->tresholdRatio->setChecked(true);
    ui->colorRadio->setChecked(false);

    for(int i = 0; i < imgSize.width(); i++)
    {
        for(int j = 0; j < imgSize.height(); j++)
        {
            QRgb color = img.pixel(i, j);
            int brightness = getBrightness(color);

            if (brightness >= devisionVal)
                img.setPixel(i, j, qRgb(255, 255, 255));
            else
                img.setPixel(i, j, qRgb(0, 0, 0));
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

void MainWindow::on_bawFormulaRadio_clicked()
{
    updateImage(&bwImg);
}

int MainWindow::getBrightness(QRgb pixel)
{
    int brightness = qRed(pixel)*RED_COEF + qGreen(pixel)*GREEN_COEF + qBlue(pixel)*BLUE_COEF;
    return brightness;
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
