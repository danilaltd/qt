#ifndef BOGO_H
#define BOGO_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef BOGOSORT_LIBRARY
    #  define BOGOSORT_EXPORT Q_DECL_EXPORT
    #else
    #  define BOGOSORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    BOGOSORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // BOGO_H
