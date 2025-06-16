#include "comb.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    double factor = 1.25;
    int step = size - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < data.size(); i++)
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i + step);
            if (data[i] > data[i + step])
            {
                qSwap(data[i], data[i + step]);
                w += 2;
            }
            r += 2;
            ++c;
            if (step / factor < 1) good.insert(i);
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        step /= factor;
    }
    look.clear();
    good.insert(size - 1);
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
