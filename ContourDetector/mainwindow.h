#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void savePicture(const QString name);

private slots:
    void on_pathButton_clicked();
    void on_trashholSlider_sliderMoved(int position);
    void on_colorRadio_clicked();
    void on_tresholdRatio_clicked();
    void on_findContourButton_clicked();
    void on_colorPeakerButton_clicked();

    void on_bwRatio_clicked();

private:
    Ui::MainWindow *ui;

    int getBrightness(QRgb pixel);
    QImage paintContour(QVector<QPoint> points);
    QVector<QPoint> findContour(QImage img);

    QImage originalImg;
    QImage tresholdedImg;
    QImage bwImg;
    QSize imgSize;

    QImage setBW(QImage img);
    QImage setTreshold(QImage img, int devisionVal);

    QString getImagePath();
    QSize getImageSize(QImage *img)
    {
        return img->size();
    }

    void showImage(QString path);
    void updateImage(QImage *img);

};

#endif // MAINWINDOW_H
