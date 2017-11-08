#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    img = image;
    ui->pathLineEdit->setText(path);
    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::convertBandW(QImage *img)
{
    QSize sizeImage = img->size();
    int width = sizeImage.width(), height = sizeImage.height();

   // QRgb color;
    int value;

    for (int i=0; i < width; i++)
    {
       for (int j=0; j < height; j++)
       {
           //QColor *color = new QColor();
           QRgb color = img->pixel(i, j);
           int gray = (qRed(color) + qGreen(color) + qBlue(color))/3;
           img->setPixel(i, j, qRgb(gray, gray, gray));
       }
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::on_trashholSlider_sliderMoved(int position)
{
    qDebug() << position;
}

void MainWindow::on_blackAndWhiteButton_clicked()
{
    convertBandW(&img);
}
