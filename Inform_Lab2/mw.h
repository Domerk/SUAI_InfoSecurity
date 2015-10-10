#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QResizeEvent>


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
    QString fileName;
    QImage imgOrig;
    QImage imgEncryp;
    QPixmap pxm1;
    QPixmap pxm2;

    virtual void resizeEvent (QResizeEvent * event);

};

#endif // MW_H
