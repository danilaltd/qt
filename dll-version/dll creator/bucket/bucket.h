#ifndef BUCKET_H
#define BUCKET_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef BUCKETSORT_LIBRARY
    #  define BUCKETSORT_EXPORT Q_DECL_EXPORT
    #else
    #  define BUCKETSORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    BUCKETSORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // BUCKET_H
