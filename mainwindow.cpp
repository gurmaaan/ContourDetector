#include "cnst.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO Нормавльный класс констант

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = ui->imageLabel;
    resize(QGuiApplication::primaryScreen()->availableSize() * SCREEN_SCALE );
    connectors();
   // imageLabel->setScaledContents(true);
  //  ui->scrolArea->setWidget(imageLabel);
  //  ui->scrolArea->setVisible(false);
   // setCentralWidget(ui->scrolArea);
}

//Инициализатор окна файловой системы в зависимости от необходимого действия (Октрыть / Сохранить)
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
//WARNING Change required
        dialog.setDirectory(!picturesLocations.isEmpty() ? OPEN_PATH_DEFAULT
                                                        : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter(TYPE_FILTER_BMP);
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix(SUFFIX_FILTER_BMP);
}


//Загружает картинку из файловой системы: проверка существования файла и типа + устанавливает необходимую трансформацию
//Возвращает статус, смог ли загрузить в итоге или нет
bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    //Если файла не существует, то выводим сообщение об ошибке, диалог не закрываем
    if (newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 ( QString(OPEN_FAILED) )
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    //Если все в порядке, обновляем изображение на экране и в оперативке, меняем заголовок окна,
    //Также выводим сообщение в статус баре с размером картинки и число бит на пиксель

    setImage(newImage);
    setWindowFilePath(fileName);
    ui->pathLE->setText(fileName);

    const QString message = ( QString(OPEN_SUCCESS) )
        .arg(QDir::toNativeSeparators(fileName)) //Имя без пути
        .arg(image.width()).arg(image.height()) //Размер
            .arg(image.depth()); // Битность
    statusBar()->showMessage(message, TIMEOUT);
    ui->scrolArea->setVisible(true);
}

void MainWindow::connectors()
{
    connect(this, imgUpdatedSignal, this, renderUi);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openAct_triggered()
{
    openImg();
}

void MainWindow::on_saveAct_triggered()
{
    saveImg(ui->pathLE->text());
}

void MainWindow::on_saveAsAct_triggered()
{
   saveImg(QFileDialog::getSaveFileName(this));
}

//Выход
void MainWindow::on_exitActr_triggered()
{
    qApp->exit(0);
}


//Полноэкранный режим
//void MainWindow::on_fullScreenAct_triggered()
//{
//    bool fullScreenMode = ui->fullScreenAct->isChecked();
//    fullScreenMode ? showFullScreen() : showNormal();
//    ui->fullScreenAct->setChecked( fullScreenMode );
//}

void MainWindow::on_clrImgAc_triggered()
{

}

void MainWindow::on_bwImgAct_triggered()
{

}

void MainWindow::on_trImgAct_triggered()
{

}

//Перезапуск
void MainWindow::on_restartAct_triggered()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

//Объединяющий метод открытия
void MainWindow::openImg()
{
    QFileDialog dialog(this, QString(OPEN_NORMAL));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while ( dialog.exec() == QDialog::Accepted
            && !loadFile( dialog.selectedFiles().first() )  ) {}
}

bool MainWindow::saveImg(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 ( QString(SAVE_FAILED) )
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }

    const QString message = ( QString(SAVED_SUCCESS) ).arg( QDir::toNativeSeparators(fileName) );
    statusBar()->showMessage(message);
    return true;
}

//Обновление состояния элементов управления в зависимости от режима просмотра изображения
void MainWindow::updateUI(MainWindow::EditorMode mode)
{

    //TODO active/inactive icons
    //bool uiActive = false, docEdited = false, notSaved = false;
    bool *state = new bool[4];
    for(auto it = state[0]; it !=state[3]; ++it ) {
        it = false;
    }

    switch (mode) {
    case  OPENED:

        //Active = true, Edited = false, HaveToSave = false
        break;
    case EDITED:
        //Active = true, Edited = true, HaveToSave = true
    case SAVED:
        //Active = true, Edited = true, HaveToSave = false
        break;
    default:
        //Active = false, Edited = false, HaveToSave = false
        break;
    }

    ui->saveAct;
    ui->saveAsAct;


}

//Копирует данные нового фалйа в поле класса
//Обновляет интерфейс
//Устанавливает трансформацию и ресайзинг

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    originalImgCopy = saveOriginalCopy(newImage);

    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = ZOOM_SCALE;
    ui->scrolArea->setVisible(true);

}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    ajustScrollBar(ui->scrolArea->horizontalScrollBar(), factor);
    ajustScrollBar(ui->scrolArea->verticalScrollBar(), factor);

    ui->zoomInAct->setEnabled(scaleFactor < 3.0);
    ui->zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainWindow::ajustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

int MainWindow::getPixelBrightness(QRgb pixel)
{
    return qRed(pixel)*RED_RATIO + qGreen(pixel)*GREEN_RATIO + qBlue(pixel)*BLUE_RATIO;
}

void MainWindow::setBW(QImage &img)
{
    for (int i = 0; i < img.size().width(); i++)
       for (int j = 0; j < img.size().height(); j++)
       {
           QRgb color = img.pixel(i, j);
           int gray = getPixelBrightness(color);
           img.setPixel(i, j, qRgb(gray, gray, gray));
       }
}

void MainWindow::fitToWindow()
{
    //imageLabel->adjustSize();
    //bool fitMode = ui->fitImgAct->isChecked();

    //ui->fitImgAct->setChecked( fitMode );

    imageLabel->resize(imageLabel->pixmap()->size());
}


void MainWindow::on_fitImgAct_triggered()
{
    ui->fitImgAct->isChecked() ?
             normalSize():  fitToWindow();
}

void MainWindow::on_pathTB_clicked()
{
    openImg();
}

void MainWindow::on_bwImgCommand_toggled(bool)
{
    setBW(image);
    emit imgUpdatedSignal();
}
