#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QResizeEvent>
#include <QLabel>
#include <QFont>
#include <fnc.h>


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
    void on_pbStart_clicked();

    void on_pbInfo_clicked();

private:
    Ui::MainWindow *ui;
    QFileDialog* fileDialog;
    QString fileName;
    QImage imgOrig;
    QImage imgEncryp;
    QPixmap pxm1;
    QPixmap pxm2;

    QLabel *info;

    fnc *MyCrypt;

    virtual void resizeEvent (QResizeEvent * event);

signals:
    void startSignal(QImage);

public slots:
    void resultSlot(QImage, double, QString);

};

#endif // MW_H
