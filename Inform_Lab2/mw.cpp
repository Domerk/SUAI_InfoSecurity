#include "mw.h"
#include "ui_mw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileDialog = new QFileDialog();

}

MainWindow::~MainWindow()
{
    delete fileDialog;
    delete ui;
}

void MainWindow::on_pbImg_clicked()
{
    fileName = fileDialog->getOpenFileName(0, tr("Выбор изображения"), "", "*.png *.bmp *.jpg *.jpeg");
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
        pxm2 = pxm1;
        ui->lblOrigin->setPixmap(pxm1);
        ui->lblCrypt->setPixmap(pxm2);
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
