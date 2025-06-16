#ifndef COUNTING_H
#define COUNTING_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef COUNTINGSORT_LIBRARY
    #  define COUNTINGSORT_EXPORT Q_DECL_EXPORT
    #else
    #  define COUNTINGSORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    COUNTINGSORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // COUNTING_H
