#include "fnc.h"

fnc::fnc(QObject *parent) : QObject(parent)
{

}

fnc::~fnc()
{

}

void fnc::startSlot(QImage newImg)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    newImg.save(&buffer, "PNG");
    buffer.close();

    Des des;

    // Вот тут нужно напилисть массив на куски по 1000 чаров

    int sizeArray = byteArray.size();

    if (sizeArray%1000 != 0)
        byteArray.resize(sizeArray + (1000 - sizeArray%1000));

    char *str1;
    char *str2;

    int i = 0;
    while (i < (sizeArray + (1000 - sizeArray%1000)))
    {
        str1 = des.Encrypt(byteArray.data() + i);
        str2 = des.Decrypt(str1 + i);
        i += 1000;
    }

    QByteArray encrypted = QByteArray::fromRawData(str1, sizeof(*str1));
    QByteArray decrypted = QByteArray::fromRawData(str2, sizeof(*str2));

    encrypted.resize(sizeArray);
    decrypted.resize(sizeArray);

    double cor = correlation(encrypted, decrypted);
    QString fd = frequencyDistribution(encrypted);

    newImg = QImage::fromData(encrypted);
    emit resultSignal(newImg, cor, fd);

}

double fnc::correlation(const QByteArray & encrypted, const QByteArray & decrypted)
{
    qint64 X = 0, Y = 0;
    long double r, divider = 0.0, denominator, xt, yt, d1 = 0.0, d2 = 0.0;

    for (char c : decrypted)
        X += uchar(c);
    for (char c : encrypted)
        Y += uchar(c);

    xt = double(X) / decrypted.size();
    yt = double(Y) / encrypted.size();

    for (int i = 0; i < decrypted.size(); i++)
    {
        divider += (double(uchar(decrypted.at(i))) - xt) *
                    double(uchar(encrypted.at(i))) - yt;
    }

    for (char c : decrypted)
        d1 += qPow(double(uchar(c)) - xt, 2);

    for (char c : encrypted)
        d2 += qPow(double(uchar(c)) - yt, 2);


    denominator = qSqrt(d1 * d2);

    r = divider / denominator;

    return r;
}


QString fnc::frequencyDistribution(const QByteArray & encrypted)
{
    qint64 _0 = 0, _1 = 0;
    for (char c : encrypted)
    {
        for (int i = 0; i < 8; i++)
            if ((c >> i) & 1)
                _1++;
        else
                _0++;
    }

    return QString(tr("%1 zeros, %2 ones, %3\% zeros, %4\% ones"))
            .arg(_0).arg(_1)
            .arg(double(_0) / (encrypted.size() * 8) * 100).arg(double(_1) / (encrypted.size() * 8) * 100);
}
