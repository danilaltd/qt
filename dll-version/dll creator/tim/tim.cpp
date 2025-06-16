#include "tim.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort) {
    callback_globe = callback;
    int size = data.size();
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    for (int i = 0; i < size; i += 16) {
        insertionSort(data, i, qMin((i + 16 - 1), (size - 1)), r, w, c, delay, pause, abort);
        callback(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    for (int size1 = 16; size1 < size; size1 = 2 * size1) {

        for (int left = 0; left < size; left += 2 * size1) {

            int mid = left + size1 - 1;
            int right = qMin((left + 2 * size1 - 1), (size - 1));

            if (mid < right)
                merge(data, left, mid, right, r, w, c, look, delay, pause, abort);
        }
    }
    for (int i = 0; i < size; ++i)
        good.insert(i);
    callback(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    QThread::msleep(delay);
    abort = true;
}

void merge(QVector<int> & data, int l, int m, int r, unsigned & read, unsigned & w, unsigned & c, QSet<int> & good, unsigned & delay, bool &pause, bool &abort)
{
    QSet<int> look;
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++){
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(l + i);
        left[i] = data[l + i];
        ++read;
        callback_globe(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    for (int i = 0; i < len2; i++){
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(m + 1 + i);
        right[i] = data[m + 1 + i];
        ++read;
        callback_globe(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        ++c;
        ++w;
        if (left[i] <= right[j]) {
            data[k] = left[i];
            i++;
        }
        else {
            data[k] = right[j];
            j++;
        }
        k++;
        callback_globe(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    while (i < len1) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        data[k] = left[i];
        ++w;
        k++;
        i++;
        callback_globe(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    while (j < len2) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        ++w;
        data[k] = right[j];
        k++;
        j++;
        callback_globe(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
}

void insertionSort(QVector<int> & data, int left, int right, unsigned & r, unsigned & w, unsigned & c, unsigned & delay, bool &pause, bool &abort)
{
    QSet<int> look, good;
    for (int i = left + 1, j, temp; i <= right; i++) {
        ++r;
        temp = data[i];
        j = i - 1;
        while (j >= left && data[j] > temp) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(j - 1);
            data[j + 1] = data[j];
            j--;
            ++w;
            ++c;
            ++r;
            callback_globe(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        data[j + 1] = temp;
        ++w;
    }
}
