#include "rearrangement.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    bool correct = false;
    int i, j, n, start, end;
    while (!correct)
    {
        n = data.size();
        i = n - 2;
        while (i >= 0 && data[i] >= data[i+1]) {
            i--;
        }
        if (i >= 0) {
            j = n - 1;
            while (j >= 0 && data[j] <= data[i]) {
                j--;
            }
            qSwap(data[i], data[j]);
        }
        start = i + 1;
        end = n - 1;
        while (start < end) {
            qSwap(data[start], data[end]);
            start++;
            end--;
        }
        correct = true;
        good.clear();
        i = size - 1;
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
    good.insert(0);
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
