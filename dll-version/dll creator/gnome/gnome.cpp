#include "gnome.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    int index = 0;
    while (size != 1 && index < size) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(index);
        look.insert(index - 1);
        if (index == 0)
            ++index;
        ++c;
        r += 2;
        if (data[index] >= data[index - 1])
            ++index;
        else {
            qSwap(data[index], data[index - 1]);
            w += 2;
            --index;
        }
        callback(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    look.clear();
    for (int i = 0; i < size; ++i) {
        good.insert(i);
    }
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
