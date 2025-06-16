#include "cocktail.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    int start = 0;
    int end = size - 1;
    int control = size - 1;
    int prStart, prEnd;

    while (start < end) {
        prStart = start, prEnd = end;
        for (int i = start; i < end; ++i) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i + 1);
            if (data[i] > data[i + 1]) {
                qSwap(data[i], data[i + 1]);
                control = i;
                w += 2;
            }
            r += 2;
            ++c;
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }

        if (start >= end)
            break;

        end = control;
        for (int i = end; i <= prEnd; ++i) good.insert(i);

        for (int i = end; i > start; --i) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i - 1);
            if (data[i] < data[i - 1]) {
                qSwap(data[i], data[i - 1]);
                control = i;
                w += 2;
            }
            r += 2;
            ++c;
            callback(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        start = control;
        for (int i = prStart; i < start; ++i) good.insert(i);
    }
    good.insert(0);
    look.clear();
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
