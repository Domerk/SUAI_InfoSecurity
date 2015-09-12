#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QChar>
#include <QVector>
#include <QTime>
#include <QtAlgorithms>

class functional: public QObject
{

    Q_OBJECT

public:
    functional(QObject *parent = 0);
    ~functional();

    struct table
    {
        QChar symbol;
        float frequency;
    };

protected:
    void encode();
    void createKey();
    void analize();
    void decript();

    bool caseTable(const table &s1, const table &s2);

    // массивы из структур для хранения частот

    QVector<table> MyFreq;
    QVector<table> GlobalFreq;


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
