#include "mainwindow.h"
#include "ui_mainwindow.h"

// ===============================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyFunc = new functional();

    connect (this, SIGNAL(newTextSIGNAL(QString)), MyFunc, SLOT(textSlot(QString)));
    connect (this, SIGNAL(showKeySIGNAL()), MyFunc, SLOT(KeySLOT()));
    connect (this, SIGNAL(showFreqSIGNAL()), MyFunc, SLOT(FreqSLOT()));
    connect (MyFunc, SIGNAL(resultSIGNAL(QString,QString,QString)), this, SLOT(resultSLOT(QString,QString,QString)));
    connect (MyFunc, SIGNAL(keySIGNAL(QString)), this, SLOT(showKeySLOT(QString)));
    connect (MyFunc, SIGNAL(freqSIGNAL(QString)), this, SLOT(showFreqSLOT(QString)));

}

// ===============================================================
void MainWindow::resultSLOT(QString encodedText, QString decryptedText, QString decText)
{

    ui->textEdit_2->insertPlainText(encodedText);
    ui->textEdit_3->insertPlainText(decryptedText);
    ui->textEdit_4->insertPlainText(decText);
}

// ===============================================================
MainWindow::~MainWindow()
{
    delete ui;
    delete MyFunc;
    delete lblKey;
    delete lblFreq;
}

// ===============================================================
// clik по зашифровать
// ===============================================================
void MainWindow::on_pushButton_clicked()
{
    QString txt = ui->textEdit->toPlainText();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    emit newTextSIGNAL(txt);
}

// ===============================================================
// показать ключ шифрования
// ===============================================================
void MainWindow::on_pushButton_3_clicked()
{
    emit showKeySIGNAL();
}

// ===============================================================
// показать таблицу частот
// ===============================================================
void MainWindow::on_pushButton_2_clicked()
{
    emit showFreqSIGNAL();
}

// ===============================================================
void MainWindow::showKeySLOT(QString str)
{

    lblKey = new QLabel(str);
    lblKey->setContentsMargins(10, 10, 10, 10);
    lblKey->setFixedSize(260, 650);
    lblKey->setWindowTitle(tr("Ключ шифрования"));
    lblKey->show();

}

// ===============================================================
void MainWindow::showFreqSLOT(QString str)
{
    lblFreq = new QLabel(str);
    lblFreq->setContentsMargins(10, 10, 10, 10);
    lblFreq->setFixedSize(370, 610);
    lblFreq->setWindowTitle(tr("Частотный криптоанализ"));
    lblFreq->show();

}
// ===============================================================
