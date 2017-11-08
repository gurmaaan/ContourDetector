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
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_pathButton_clicked();
    void on_trashholSlider_sliderMoved(int position);
    void on_colorRadio_clicked();
    void on_bawDevide3Radio_clicked();
    void on_bawFormulaRadio_clicked();

private:
    Ui::MainWindow *ui;
    int getBrightness(int red, int green, int blue);
    QImage originalImg;
    QImage BandWImgDevide3;
    QImage BandWImgFormula;
    QImage convertBandWDevide3(QImage img);
    QImage convertBandWFormula(QImage img);
    void setTreshold(QImage img, int devisionVal);
    QSize imgSize;
    QString getImagePath();
    void showImage(QString path);
    void updateImage(QImage *img);

    QSize getImageSize(QImage *img)
    {
        return img->size();
    }
};

#endif // MAINWINDOW_H
