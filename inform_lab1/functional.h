#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <QWidget>
#include <QString>
#include <QMap>
#include <QChar>
#include <QTime>

struct table
{
    QChar symbol;
    float frequency;
};

class functional: public QWidget
{

    Q_OBJECT

public:
    functional(QWidget *parent = 0);
    ~functional();

protected:
    void encode();
    void createKey();
    void analize();

    // массивы из структур для хранения частот
    table MyFreq[26];
    table GlobalFreq[26];

    // массив для хранения символов подстановки
    QMap<QChar, QChar> KeyMap;

    // строки, с которыми будем работать
    QString text;
    QString encoded;
    QString decrypted;
    QString dectext;

    int a, b, m;

public slots:
    void textSlot (QString newText);

signals:
    void resultSIGNAL (QString encoded, QString decrypted, QString dectext);

};

#endif // FUNCTIONAL_H
