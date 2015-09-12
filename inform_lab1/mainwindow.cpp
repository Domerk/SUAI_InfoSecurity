#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyFunc = new functional();

    connect (this, SIGNAL(newTextSIGNAL(QString)), MyFunc, SLOT(textSlot(QString)));
    connect (MyFunc, SIGNAL(resultSIGNAL(QString,QString,QString)), this, SLOT(resultSLOT(QString,QString,QString)));

}

void MainWindow::resultSLOT(QString encodedText, QString decryptedText, QString decText)
{

    ui->textEdit_2->insertPlainText(encodedText);
    ui->textEdit_3->insertPlainText(decryptedText);
    ui->textEdit_4->insertPlainText(decText);
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
    ui->pushButton->setEnabled(false);

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
