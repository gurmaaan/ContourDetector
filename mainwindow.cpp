#include "cnst.h"
#include "mainwindow.h"
#include <QDir>
#include "ui_mainwindow.h"

//TOD Ресайзинг и скейлинг
//TODO Сохранение

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    core(new ImgProc),
    imageLabel(new QLabel)
{
    ui->setupUi(this);
    switchState(AppState::FileOpened);
    imageLabel = ui->imageLabel;
    resize(QGuiApplication::primaryScreen()->availableSize() * SCREEN_SCALE );

    imageLabel->setScaledContents(true);

   // setCentralWidget(ui->scrolArea);
}

//Инициализатор окна файловой системы в зависимости от необходимого действия (Октрыть / Сохранить)
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList myPicturesPath = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory( !myPicturesPath.isEmpty() ? QApplication::applicationFilePath() : myPicturesPath.last() ); //WARNING Change required
    }

    //Создали лист бит => получаем список поддерживаемыхх форматов системй!! в зависимости от открытия или сохранения картинки
    const QByteArrayList supportedTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();

    //Из полученного массива извлекаем строки названия формата по которому будут фильтроваться файлы в диалоге (поддерживаемые типы картинок)
    QStringList typeFilter;
    foreach (const QByteArray &mimeTypeName, supportedTypes)
        typeFilter.append(mimeTypeName);
    //typeFilter.sort();

    dialog.setMimeTypeFilters(typeFilter); //Установить фильтр на файлы - отображать только изображения любого типа (как в списке так и видно)
    dialog.selectMimeTypeFilter(MIME_ALL); //Среди полученных выбрать группу опр формата

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix( S_F_ALL ); //При сохранении сам добавляет выбранный суффикс (.формат) к файлы
    //При выборе картинки роли не играет
}

//Функция запускаемая по нажатию кнопки - создаем диаллог, передаем в функцию загрузки
void MainWindow::openImg()
{
    QFileDialog dialog(this);
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    //Пока код выхода диалога равен не ноль (окно открыто) ждем когда функция loadFile прочитает сам файл
    //Функция считывания ждем пока диалог не вернет список
    while ( dialog.exec() == QDialog::Accepted &&
            !loadFile( dialog.selectedFiles().first() )  ) {
        //Никогда не исполнется
    }
}

//На вход стандартный диалог, кот превращаетсчя в считыватель изображений
bool MainWindow::loadFile(const QString &fileName)
{
    //Иници
    QImageReader reader(fileName);
    reader.setAutoTransform(false);
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
    qDebug() << message;
    statusBar()->showMessage(message, TIMEOUT);
    ui->scrolArea->setVisible(true);
    return true;
}

void MainWindow::updateView(const QImage &newImage)
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::switchState(MainWindow::AppState mode)
{
   // bool fno = mode ? true : false;
    ui->imageViewDockContent->setEnabled(mode);
    ui->saveAct->setEnabled(mode);
    ui->saveAsAct->setEnabled(mode);
    ui->viewTB->setEnabled(mode);
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

    scaleFactor = ZOOM_SCALE;
    ui->scrolArea->setVisible(true);
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(ui->imageLabel->pixmap());
    scaleFactor *= factor;
    ui->imageLabel->resize(scaleFactor * ui->imageLabel->pixmap()->size());

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
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->resize(image.size());
}

void MainWindow::normalSize() {
    ui->imageLabel->adjustSize();
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
    updateView( core->getImgTr( ui->trLevelSB->value() ) );
}


void MainWindow::on_zoomInAct_triggered()
{
        zoomIn();

}

void MainWindow::on_zoomOutAct_triggered()
{
        zoomOut();
}

void MainWindow::on_tresholdSlider_sliderMoved(int position)
{
    updateView( core->getImgTr(position) );
}
