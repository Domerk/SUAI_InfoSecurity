#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include "functional.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    functional *MyFunc;
    QLabel *lblKey;
    QLabel *lblFreq;


public slots:
    void resultSLOT(QString encodedText, QString decryptedText, QString decText);
    void showKeySLOT(QString str);
    void showFreqSLOT(QString str);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

signals:
    void newTextSIGNAL(QString txt);
    void showKeySIGNAL();
    void showFreqSIGNAL();
};

#endif // MAINWINDOW_H
