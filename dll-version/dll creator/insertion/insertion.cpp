#include "insertion.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good, f;
    unsigned r = 0, w = 0, c = 0;
    int key;
    for (int i = 0, j; i < size; ++i) {
        f.insert(i);
        key = data[i];
        ++r;
        j = i;
        while (j > 0 && data[j - 1] > key){
            ++c;
            ++r;
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(j - 1);
            data[j] = data[j - 1];
            ++w;
            --j;
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        data[j] = key;
        ++w;
    }
    look.clear();
    callback(data, look, f, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
