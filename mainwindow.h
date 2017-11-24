#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringList>
#include <QDebug>
#include <QProcess>
#include <QScreen>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QScrollBar>
#include <QImage>
#include <QBitmap>

#include "cnst.h"
#include "imgproc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ImgProc *core;
    Cnst config;

    bool loadFile(const QString &);

public slots:
    void updateView(const QImage &newImage);
    void viewerModeToggleEnabled(bool state);

private slots:
    void on_openAct_triggered();
    void on_saveAct_triggered();
    void on_saveAsAct_triggered();
    void on_pathTB_clicked();

    void on_exitActr_triggered();
    void on_restartAct_triggered();

    void on_fitImgAct_triggered();

    void on_zoomInAct_triggered();
    void on_zoomOutAct_triggered();
   // void on_trManualGB_toggled(bool arg1);
    //void on_tresholdSlider_sliderMoved(int position);

    void on_clrImgAc_triggered();
    void on_bwImgAct_triggered();
    void on_trImgAct_triggered();

    void on_clrImgCommand_toggled(bool checked);
    void on_bwImgCommand_toggled(bool checked);
    void on_trImgCommand_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QImage image;

    double scaleFactor;

    void setImage(const QImage &newImage);

    void scaleImage(double factor);
    void ajustScrollBar(QScrollBar *scrollBar, double factor);
    void openImg();
    bool saveImg(const QString &fileName);

    void fitToWindow();
    void normalSize();
    void zoomIn();
    void zoomOut();
};


#endif // MAINWINDOW_H
