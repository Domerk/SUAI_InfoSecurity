#include "functional.h"

// конструктор
functional::functional(QWidget *parent)
    : QWidget(parent)
{
        GlobalFreq[0].symbol ='e';
        GlobalFreq[0].frequency = 12.7;

        GlobalFreq[1].symbol ='t';
        GlobalFreq[1].frequency = 9.06;

        GlobalFreq[2].symbol ='a';
        GlobalFreq[2].frequency = 8.17;

        GlobalFreq[3].symbol ='o';
        GlobalFreq[3].frequency = 7.51;

        GlobalFreq[4].symbol ='i';
        GlobalFreq[4].frequency = 6.97;

        GlobalFreq[5].symbol ='n';
        GlobalFreq[5].frequency = 6.75;

        GlobalFreq[6].symbol ='s';
        GlobalFreq[6].frequency = 6.33;

        GlobalFreq[7].symbol ='h';
        GlobalFreq[7].frequency = 6.09;

        GlobalFreq[8].symbol ='r';
        GlobalFreq[8].frequency = 5.99;

        GlobalFreq[9].symbol ='d';
        GlobalFreq[9].frequency = 4.25;

        GlobalFreq[10].symbol ='l';
        GlobalFreq[10].frequency = 4.03;

        GlobalFreq[11].symbol ='c';
        GlobalFreq[11].frequency = 2.78;

        GlobalFreq[12].symbol ='u';
        GlobalFreq[12].frequency = 2.76;

        GlobalFreq[13].symbol ='m';
        GlobalFreq[13].frequency = 2.41;

        GlobalFreq[14].symbol ='w';
        GlobalFreq[14].frequency = 2.36;

        GlobalFreq[15].symbol ='f';
        GlobalFreq[15].frequency = 2.23;

        GlobalFreq[16].symbol ='g';
        GlobalFreq[16].frequency = 2.02;

        GlobalFreq[17].symbol ='y';
        GlobalFreq[17].frequency = 1.97;

        GlobalFreq[18].symbol ='p';
        GlobalFreq[18].frequency = 1.93;

        GlobalFreq[19].symbol ='b';
        GlobalFreq[19].frequency = 1.49;

        GlobalFreq[20].symbol ='v';
        GlobalFreq[20].frequency = 0.98;

        GlobalFreq[21].symbol ='k';
        GlobalFreq[21].frequency = 0.77;

        GlobalFreq[22].symbol ='j';
        GlobalFreq[22].frequency = 0.15;

        GlobalFreq[23].symbol ='x';
        GlobalFreq[23].frequency = 0.15;

        GlobalFreq[24].symbol ='q';
        GlobalFreq[24].frequency = 0.1;

        GlobalFreq[25].symbol ='z';
        GlobalFreq[25].frequency = 0.07;

        int x = 0;
        for (char i='a'; i<='z'; i++)
        {
            MyFreq[x].symbol = (QChar)i;
            MyFreq[x].frequency = 0;
            x++;
        }

}

// формируем ключ и таблицу, по которой происходит подмена
void functional::createKey()
{
    // возможные значения а: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 и 25
    // то есть это нечётное число в диапазоне от 1 до 25, за исключением 13

    a = 13;
    while (a == 13)
    {
        a = 1 + 2*qrand()%12;
    }

    // b - любое число, но желательно, чтобы это была не 1
    // заодно сделаем его не слишком большим
    // всё равно это псевдослучайное число
    b = qrand()%102 + 2;

    // формируем промежуточный массив "символ - номер символа-замены"
    int isymbols[26];
    char csymbols[26];
    int x = 0;
    char i;
    for (i='a'; i<='z'; i++)
    {
        isymbols[i]=(a*x + b)%26;
        csymbols[x]=i;
        x++;
    }

    // формируем таблицу замены
    for (i='a'; i<='z'; i++)
    {
        KeyMap[i] = csymbols[isymbols[i]];
    }

}


// функция шифрования исходного текста
void functional:: encode()
{
    encoded = text;
    int textLenght = encoded.length();

    for (int i = 0; i<textLenght; i++)
    {
       encoded[i] = KeyMap[text[i]];
    }

}


// функция частотного анализа
void functional::analize()
{
    // получаем таблицу символ - частота
    for (int i=0; i<=26; i++)
    {
        MyFreq[i].frequency = encoded.count(MyFreq[i].symbol);
    }

    // тут должна быть сортировка MyFreq


    decrypted = encoded;
    int textLenght = decrypted.length();

   /* for (int i = 0; i<textLenght; i++)
    {
      // decrypted[i] =
    } */

}


void functional::textSlot(QString newText)
{
    // получили текст
    text = newText;
    // генерируем ключ
    createKey();
    // шифруем
    encode();
    // пытаемся взломать
    analize();
    emit resultSIGNAL(encoded, decrypted, dectext);
}

// деструктор
functional::~functional()
{

}

