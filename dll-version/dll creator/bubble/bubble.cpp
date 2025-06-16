#include "bubble.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    int size = data.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(j);
            look.insert(j + 1);
            if (data[j] > data[j + 1]) {
                qSwap(data[j], data[j + 1]);
                w += 2;
            }
            r += 2;
            ++c;
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        good.insert(size - i - 1);
    }
    good.insert(0);
    look.clear();
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
