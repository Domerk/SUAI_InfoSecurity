#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPainter>
#include <QWidget>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbImg_clicked();

private:
    Ui::MainWindow *ui;
    QFileDialog* fileDialog;
    QString* fileName;
    QImage imgOrig;
    QImage imgEncryp;

    QWidget* wgt1;
    QWidget* wgt2;

    QPainter* p1;
    QPainter* p2;


};

#endif // MW_H
