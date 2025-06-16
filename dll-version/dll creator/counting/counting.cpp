#include "counting.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    int size = data.size();
    QSet<int> look, good, f;
    QMap<int, int> count;
    auto data1 = data;
    unsigned r = 0, w = 0, c = 0;

    look.clear();
    for (int i = 0; i < size; ++i) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(i);
        good.insert(i);
        ++count[data[i]];
        ++r;
        callback(data, look, f, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    look.clear();
    data.clear();
    for (int i = 0; i <= size; ++i){
        data.insert(data.cend(), count[i], i);
        w += count[i];
        if (!data.empty())
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            for (int j = 1; j <= count[i]; ++j) {
                look.insert(data.size() - j);
            }
            data1 = data;
            // data1.insert(data1.cend(), count[i], /*size - data1.size()*/0);
            callback(data1, look, f, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
    }
    look.clear();
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
