#include "mw.h"
#include "ui_mw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileDialog = new QFileDialog();
    fileName = new QString();




}

MainWindow::~MainWindow()
{
    delete fileDialog;
    delete fileName;
    delete ui;
}

void MainWindow::on_pbImg_clicked()
{
    QString fn = fileDialog->getOpenFileName(0, tr("Выбор изображения"), "", "*.png *.bmp *.jpg *.jpeg");
    if (!fn.isEmpty())
    {
        QImage img(fn);
        pxm1.load(fn);
        if (pxm1.height() > 300 || pxm1.width() > 300)
            pxm1 = pxm1.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        if (img.format() != QImage::Format_Invalid)
            {
                imgOrig = img;
                ui->lblOrigin->setPixmap(pxm1);
                ui->lblCrypt->setPixmap(pxm1);
            }

    }


}
