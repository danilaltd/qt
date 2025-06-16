#include "bogo.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    QSet<int> look, good;
    int size = data.size();
    unsigned r = 0, w = 0, c = 0;
    bool correct = size == 1;
    int i = 0, j;
    while (!correct){
        good.clear();
        for (i = 0; i < size; ++i){
            look.clear();
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            j = QRandomGenerator::global()->bounded(0, size);
            look.insert(i);
            look.insert(j);
            qSwap(data[i], data[j]);
            w += 2;
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        look.clear();
        --i;
        correct = true;
        while (i > 0){
            ++r;
            ++c;
            if (data[i - 1] > data[i]){
                correct = false;
                break;
            }
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            good.insert(i);
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
            --i;
        }
    }

    good.insert(i);
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
