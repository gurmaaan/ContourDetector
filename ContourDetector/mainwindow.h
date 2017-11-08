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

    void on_blackAndWhiteButton_clicked();

private:
    Ui::MainWindow *ui;
    QImage img;
    QString getImagePath();
    void showImage(QString path);
    void convertBandW(QImage *img);
};

#endif // MAINWINDOW_H
