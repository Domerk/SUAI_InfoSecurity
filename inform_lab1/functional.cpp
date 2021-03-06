#include "functional.h"

// ===============================================================
// конструктор
// ===============================================================
functional::functional(QObject *parent)
    : QObject(parent)
{
    // заполняем таблицу частот встречаемости букв в английском языке
    // используем строчные символы

    // да, это выглядит просто жесть

    for (char i='a'; i<='z'; i++)
    {
        GlobalFreq.push_back({' ', 0.0});
        MyFreq.push_back({i, 0.0});
    }

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

        // создаём шаблон для таблицы частот встречаемости символов
        // введённого пользователем текста

}

// ===============================================================
// ===============================================================
bool caseTableLessThan(const functional::table &s1, const functional::table &s2)
{
    return s1.frequency > s2.frequency;
}

// ===============================================================
// формируем ключ и таблицу, по которой происходит подмена
// ===============================================================
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
    QMap <char, int> isymbols;
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
        DecMap[csymbols[isymbols[i]]]=(QChar)i;
    }

}

// ===============================================================
// функция шифрования исходного текста
// ===============================================================
void functional:: encode()
{
    encoded = text;
    int textLenght = encoded.length();

    // вот тут учесть, что в строке есть не только букы
    // но и всякие там пробелы и тому подобное
    for (int i = 0; i<textLenght; i++)
    {
        // проверка на то, является ли символ буквой
        // если символ не буква, то ничего с ним не делаем
        // регистр игнорируется
       if (encoded[i].isLetter())
       {
           if (encoded[i].isUpper())
           {
               encoded[i] = KeyMap[text[i].toLower()].toUpper();
           }
           else
           {
               encoded[i] = KeyMap[text[i]];
           }
       }
    }
}

// ===============================================================
// функция частотного анализа
// ===============================================================
void functional::analize()
{

    decrypted = encoded;
    int textLenght = decrypted.length();

    // получаем таблицу символ - частота
    // частоты представляем в процентах
    for (int i=0; i<26; i++)
    {
        // получаем количественное значение
        MyFreq[i].frequency = encoded.count(MyFreq[i].symbol);
        // переводим его в проценты
        MyFreq[i].frequency = (MyFreq[i].frequency / textLenght)*100;

    }

    qSort(MyFreq.begin(), MyFreq.end(), caseTableLessThan);

    for (int i = 0; i<26; i++)
    {
        FreqMap[MyFreq[i].symbol] = GlobalFreq[i].symbol;
    }


    for (int i = 0; i<textLenght; i++)
    {
        if (decrypted[i].isLetter())
        {
            if (decrypted[i].isUpper())
            {
                decrypted[i] = FreqMap[encoded[i].toLower()].toUpper();
            }
            else
            {
                decrypted[i] = FreqMap[encoded[i]];
            }
        }
    }

}

// ===============================================================
// ===============================================================
void functional::decript()
{
    dectext = encoded;
    int textLenght = dectext.length();

    for (int i = 0; i<textLenght; i++)
    {
        if (dectext[i].isLetter())
        {
            if (dectext[i].isUpper())
            {
                dectext[i] = DecMap[encoded[i].toLower()].toUpper();
            }
            else
            {
                dectext[i] = DecMap[encoded[i]];
            }
        }
    }

}

// ===============================================================
// ===============================================================
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
    // дешифруем
    decript();
    emit resultSIGNAL(encoded, decrypted, dectext);
}

// ===============================================================
// ===============================================================
void functional::KeySLOT()
{
    // формируем строку - вывод значений ключей
    QString str;
    str.append(tr("<p>Ключ шифрования: а = "));
    str.append(QString::number(a, 10));
    str.append(tr(", b = "));
    str.append(QString::number(b, 10));
    str.append("</p><br /><table border = 1 cellpadding = 2><tr><td><b>Исходный символ</b></td><td><b>Символы замены</b></td></tr>");

    for (char i = 'a'; i<='z'; i++)
    {
        str.append("<tr><td>");
        str.append(QChar(i));
        str.append("</td><td>");
        str.append(KeyMap[QChar(i)]);
        str.append("</td></tr>");
    }

    str.append("</table>");

    emit keySIGNAL(str);
}

// ===============================================================
// ===============================================================
void functional::FreqSLOT()
{
    // формируем строку - вывод частотного анализа
    QString str;

    str.append("<table border = 1 cellpadding = 2><tr><td><b>Символ текста</b></td><td><b>Частота</b></td><td><b>Символ алфавита</b></td><td><b>Частота</b></td></tr>");

    for (int i = 0; i<26; i++)
    {

        str.append("<tr><td>");
        str.append(MyFreq[i].symbol);
        str.append("</td><td>");
        str.append(QString::number(MyFreq[i].frequency, 10, 2));
        str.append("</td><td>");
        str.append(GlobalFreq[i].symbol);
        str.append("</td><td>");
        str.append(QString::number(GlobalFreq[i].frequency, 10, 2));
        str.append("</td></tr>");
    }

    str.append("</table>");

    emit freqSIGNAL(str);

}

// ===============================================================
// деструктор
// ===============================================================
functional::~functional()
{

}

