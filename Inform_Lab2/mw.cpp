#include "mw.h"
#include "ui_mw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Алгоритм шифрования DES"));

    fileDialog = new QFileDialog();
    MyCrypt = new fnc();

    ui->pbStart->setEnabled(false);
    ui->pbInfo->setEnabled(false);

    info = new QLabel();
    info->setWindowTitle(tr("Статистика"));
    info->setContentsMargins(10, 10, 10, 10);

    QFont font = info->font();
    font.setPixelSize(12);
    info->setFont(font);

    connect (this, SIGNAL(startSignal(QImage)), MyCrypt, SLOT(startSlot(QImage)));
    connect (MyCrypt, SIGNAL(resultSignal(QImage, double, QString)), this, SLOT(resultSlot(QImage, double, QString)));

}

MainWindow::~MainWindow()
{
    delete fileDialog;
    delete MyCrypt;
    delete info;
    delete ui;
}

void MainWindow::on_pbImg_clicked()
{
    //fileName = fileDialog->getOpenFileName(0, tr("Выбор изображения"), "", "*.png *.bmp *.jpg *.jpeg");
    fileName = fileDialog->getOpenFileName(0, tr("Выбор изображения"), "", "*.png");
    if (!fileName.isEmpty())
    {
        QImage img(fileName);

        if (img.format() != QImage::Format_Invalid)
        {

        pxm1.load(fileName);
        if (pxm1.height() > 300 || pxm1.width() > 300)
            pxm1 = pxm1.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        imgOrig = img;
        imgEncryp = img;
        ui->lblOrigin->setPixmap(pxm1);

        ui->pbStart->setEnabled(true);
        ui->pbInfo->setEnabled(true);
        }
    }
}

void MainWindow::resizeEvent (QResizeEvent * event)
{
    int w = ui->centralWidget->width() / 2;
    int h = ui->lblOrigin->height() - ui->pbImg->height();

    if (!pxm1.isNull())
    {
        pxm1 = pxm1.fromImage(imgOrig);
        pxm1 = pxm1.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lblOrigin->setPixmap(pxm1);
    }

    if (!pxm2.isNull())
    {
        pxm2 = pxm2.fromImage(imgEncryp);
        pxm2 = pxm2.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lblCrypt->setPixmap(pxm2);
    }
}

void MainWindow::on_pbStart_clicked()
{
    emit startSignal(imgOrig);
}

void MainWindow::resultSlot(QImage resultImg, double correlation, QString frequencyDistribution)
{
    imgEncryp = resultImg;

    int w = pxm2.width();
    int h = pxm2.height();

    pxm2 = pxm2.fromImage(imgEncryp);
    pxm2 = pxm2.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->lblCrypt->setPixmap(pxm2);

    QString result;
    result.append(tr("<p>Коэфиициент корреляции: "));
    result.append(QString::number(correlation, 10, 3));
    result.append(tr("</p><p>Частотное распределение:<br>"));
    result.append(frequencyDistribution);
    result.append("</p>");

    info->setText(result);
}

void MainWindow::on_pbInfo_clicked()
{
    info->show();
}
