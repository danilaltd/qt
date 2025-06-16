#include "bucket.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good, f;
    unsigned r = 0, w = 0, c = 0;
    QVector<QVector <int>> bucket(10);
    int d = 1, dd = size, cnt = 0, l;
    while(dd > 0)
    {
        cnt++;
        dd /= 10;
    }
    for(int m = 0; m < cnt; m++)
    {
        for (int i = 0; i < 10; ++i) {
            bucket[i].clear();
        }
        for(int i = 0; i < size; i++)
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            bucket[(data[i] / d) % 10].push_back(data[i]);
            ++r;
            look.clear();
            look.insert(i);
            callback(data, look, f, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }

        l = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int k = 0; k < bucket[i].size(); k++)
            {
                data[l] = bucket[i][k];
                ++l;
                ++w;
                look.clear();
                look.insert(l);
                while (pause && !abort) {
                    QCoreApplication::processEvents();
                }
                if (abort) return;
                callback(data, look, f, r, w, c);
                QCoreApplication::processEvents();
                QThread::msleep(delay);
            }
        }
        d *= 10;
        look.clear();
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        callback(data, look, f, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    for (int i = 0; i < size; ++i) {
        good.insert(i);
    }
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    QThread::msleep(delay);
    abort = true;
}
