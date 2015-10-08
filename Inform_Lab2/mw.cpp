#include "mw.h"
#include "ui_mw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileDialog = new QFileDialog();
    fileName = new QString();

    wgt1 = new QWidget();
    wgt2 = new QWidget();

    p1 = new QPainter(wgt1);
    p1 = new QPainter(wgt2);

    ui->horizontalLayout->addWidget(wgt1);
    ui->horizontalLayout->addWidget(wgt2);

    wgt1->setMinimumSize(300, 300);
    wgt1->setMaximumSize(800, 800);
    wgt1->show();

    wgt2->setMinimumSize(300, 300);
    wgt2->setMaximumSize(800, 800);
    wgt2->show();


}

MainWindow::~MainWindow()
{
    delete fileDialog;
    delete fileName;
    delete p1;
    delete p2;
    delete wgt1;
    delete wgt2;
    delete ui;
}

void MainWindow::on_pbImg_clicked()
{
    QString fn = fileDialog->getOpenFileName(0, tr("Выбор изображения"), "", "*.png *.bmp *.jpg *.jpeg");
    if (!fn.isEmpty())
    {
        QImage img(fn);
        if (img.format() != QImage::Format_Invalid)
            {
                imgOrig = img;
                p1->drawImage(0, 0, imgOrig);
            }

    }


}
