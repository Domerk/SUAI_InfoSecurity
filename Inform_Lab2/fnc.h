#ifndef FNC_H
#define FNC_H

#include <QObject>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QString>
#include <QtCore/qmath.h>
#include <des.h>

class fnc : public QObject
{
    Q_OBJECT
public:
    explicit fnc(QObject *parent = 0);
    ~fnc();

protected:
    double correlation(const QByteArray & encrypted, const QByteArray & decrypted);
    QString frequencyDistribution(const QByteArray & encrypted);

signals:
    void resultSignal(QImage, double, QString);

public slots:
    void startSlot(QImage);
};

#endif // FNC_H
