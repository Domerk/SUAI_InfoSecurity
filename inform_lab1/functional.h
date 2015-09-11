#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QChar>
#include <QTime>

struct table
{
    QChar symbol;
    float frequency;
};

class functional: public QObject
{

    Q_OBJECT

public:
    functional(QObject *parent = 0);
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

    // ещё две карты, которые, возможно, не пригодятся
    QMap<QChar, QChar> FreqMap;
    QMap<QChar, QChar> DecMap;

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
