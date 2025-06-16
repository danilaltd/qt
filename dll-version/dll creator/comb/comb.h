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

}


#endif // BUBBLE_H
