#ifndef INSERTION_H
#define INSERTION_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef INSERTION_LIBRARY
    #  define INSERTION_EXPORT Q_DECL_EXPORT
    #else
    #  define INSERTION_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    INSERTION_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // INSERTION_H
