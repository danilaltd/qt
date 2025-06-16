#ifndef REARRANGEMENT_H
#define REARRANGEMENT_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef REARRANGEMENTSORT_LIBRARY
    #  define REARRANGEMENTSORT_EXPORT Q_DECL_EXPORT
    #else
    #  define REARRANGEMENTSORT_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    REARRANGEMENTSORT_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // REARRANGEMENT_H
