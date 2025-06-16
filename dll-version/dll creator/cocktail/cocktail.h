#ifndef COCKTAIL_H
#define COCKTAIL_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef COCKTAILSORT_LIBRARY
    #  define COCKTAILSORT_EXPORT Q_DECL_EXPORT
    #else
    #  define COCKTAILSORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    COCKTAILSORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // COCKTAIL_H
