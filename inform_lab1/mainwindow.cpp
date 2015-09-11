#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->textEdit_2->hide();
    ui->label_3->hide();

    ui->textEdit_3->hide();
    ui->label_4->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label_5->hide();
    ui->textEdit_4->hide();

    MyFunc = new functional();

    connect (this, SIGNAL(newTextSIGNAL(QString)), MyFunc, SLOT(textSlot(QString)));
    connect (MyFunc, SIGNAL(resultSIGNAL(QString,QString,QString)), this, SLOT(resultSLOT(QString,QString,QString)));

}

void MainWindow::resultSLOT(QString encodedText, QString decryptedText, QString decText)
{

    ui->textEdit_2->insertPlainText(encodedText);
    ui->textEdit_2->show();
    ui->label_3->show();

    ui->textEdit_3->insertPlainText(decryptedText);
    ui->textEdit_3->show();
    ui->label_4->show();

    ui->label_5->show();

    ui->textEdit_4->insertPlainText(decText);
    ui->textEdit_4->show();

    ui->pushButton_2->show();
    ui->pushButton_3->show();

    // как-то сделать так, чтобы главное окно увеличивалось в размерах и появлялся скролл!!!

}

MainWindow::~MainWindow()
{
    delete ui;
    delete MyFunc;
}

// clik по зашифровать
void MainWindow::on_pushButton_clicked()
{
    //заблокировать кнопку после нажатия!!!!
    //ui->pushButton->

    QString txt = ui->textEdit->toPlainText();
    emit newTextSIGNAL(txt);
}

// показать ключ шифрования
void MainWindow::on_pushButton_3_clicked()
{

}

// показать таблицу частот
void MainWindow::on_pushButton_2_clicked()
{

}
