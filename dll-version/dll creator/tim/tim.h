#ifndef BUBBLE_H
#define BUBBLE_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef BUBBLESORT_LIBRARY
    #  define BUBBLESORT_EXPORT Q_DECL_EXPORT
    #else
    #  define BUBBLESORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    BUBBLESORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);
    ArrayToSceneFunction callback_globe;
    void merge(QVector<int> &, int, int, int, unsigned &, unsigned &, unsigned &, QSet<int> &, unsigned int &, bool &, bool &);
    void insertionSort(QVector<int> &, int, int, unsigned &, unsigned &, unsigned &, unsigned int &, bool &, bool &);
}


#endif // BUBBLE_H
