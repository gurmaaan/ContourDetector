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
#include "cnst.h"
#include <QScrollBar>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &);
    enum EditorMode {
        NOTHING, OPENED, EDITED, SAVED
    };

    Cnst config;
    void connectors();


private slots:
    void on_openAct_triggered();
    void on_saveAct_triggered();
    void on_saveAsAct_triggered();

    void on_exitActr_triggered();
    //void on_fullScreenAct_triggered();
    void on_clrImgAc_triggered();
    void on_bwImgAct_triggered();
    void on_trImgAct_triggered();
    void on_restartAct_triggered();

    void openImg();
    bool saveImg(const QString &fileName);

    void updateUI(EditorMode mode);

    void renderUi(bool trigger);
    void on_fitImgAct_triggered();

    void on_pathTB_clicked();

    void on_bwImgCommand_toggled(bool);


private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QImage image;

    QImage originalImgCopy;
    double scaleFactor;

    void setImage(const QImage &newImage);

    inline QImage saveOriginalCopy(const QImage &newImage) {
        return newImage;
    }

    void scaleImage(double factor);
    void ajustScrollBar(QScrollBar *scrollBar, double factor);

    int getPixelBrightness(QRgb pixel);
    void setBW(QImage &img);

    void fitToWindow();
        inline void normalSize() {
        imageLabel->adjustSize();
        scaleFactor = 1;
    }

    inline void zoomIn() {
        scaleImage(1.25);
    }

    inline void zoomOut() {
        scaleImage(0.8);
    }

signals:
        void imgUpdatedSignal();

};


#endif // MAINWINDOW_H
