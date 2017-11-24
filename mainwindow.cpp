#include "cnst.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO Нормавльный класс констант
//TODO Синхронное переключение выпадающего меню и кнопок при изменении вида
//Ресайзинг и скейлинг

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = ui->imageLabel;
    core = new ImgProc();
    resize(QGuiApplication::primaryScreen()->availableSize() * SCREEN_SCALE );
    viewerModeToggleEnabled(false);
   // imageLabel->setScaledContents(true);
  //  ui->scrolArea->setWidget(imageLabel);
  //  ui->scrolArea->setVisible(false);
   // setCentralWidget(ui->scrolArea);
}

//Инициализатор окна файловой системы в зависимости от необходимого действия (Октрыть / Сохранить)
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
//WARNING Change required
        dialog.setDirectory(!picturesLocations.isEmpty() ? OPEN_PATH_DEFAULT : picturesLocations.last());
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
    return true;
}

void MainWindow::updateView(const QImage &newImage)
{
    imageLabel->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::viewerModeToggleEnabled(bool state)
{
    ui->imageViewDock->setEnabled(state);

    ui->clrImgAc->setEnabled(state);
    ui->bwImgAct->setEnabled(state);
    ui->trImgAct->setEnabled(state);
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

////Обновление состояния элементов управления в зависимости от режима просмотра изображения


//Копирует данные нового фалйа в поле класса
//Обновляет интерфейс
//Устанавливает трансформацию и ресайзинг

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    core->loadImage(newImage);
    updateView( core->getImgClr() );
    viewerModeToggleEnabled( !newImage.isNull() );
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

void MainWindow::fitToWindow()
{
    ui->scrolArea->setWidgetResizable(true);
    imageLabel->setScaledContents(true);
    imageLabel->resize(image.size());
}

void MainWindow::normalSize() {
    imageLabel->adjustSize();
    scaleFactor = 1;
}

void MainWindow::zoomIn() {
    scaleImage(1.25);
}

void MainWindow::zoomOut() {
    scaleImage(0.8);
}

void MainWindow::on_fitImgAct_triggered()
{
    ui->fitImgAct->isChecked() ? normalSize() :  fitToWindow();
}

void MainWindow::on_pathTB_clicked()
{
    openImg();
}

//Toggle эмитится при переключении состояния группы кнопок
//Если убрать проверку на checked, то событие отрабатывается 2 раза
//При смене состояния группы кнопок эмитится соответсвующее действие
void MainWindow::on_clrImgCommand_toggled(bool checked)
{
    if ( checked )
        ui->clrImgAc->triggered(true);
}

void MainWindow::on_bwImgCommand_toggled(bool checked)
{
    if ( checked )
        ui->bwImgAct->triggered(true);
}

void MainWindow::on_trImgCommand_toggled(bool checked)
{
    if ( checked )
        ui->trImgAct->triggered(true);
}


void MainWindow::on_clrImgAc_triggered()
{
    updateView( core->getImgClr() );
}

void MainWindow::on_bwImgAct_triggered()
{
    updateView( core->getImgBw() );
    ui->trLevelSB->setValue( core->getAutoTr() );
}

void MainWindow::on_trImgAct_triggered()
{

}


void MainWindow::on_zoomInAct_triggered()
{
        zoomIn();

}

void MainWindow::on_zoomOutAct_triggered()
{
        zoomOut();
}

//void MainWindow::on_trManualGB_toggled(bool arg1)
//{
//    arg1 ? trImage = setTresholdAuto(image) : setTresholdManual(image, ui->tresholdSlider->value());
//    imageLabel->setPixmap(setTresholdAuto(trImage));
//}

//void MainWindow::on_tresholdSlider_sliderMoved(int position)
//{

//}
