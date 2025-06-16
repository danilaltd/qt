#ifndef GNOME_H
#define GNOME_H

#include <QVector>
#include <QSet>

extern "C" {

    #ifdef GNOME_LIBRARY
    #  define GNOME_EXPORT Q_DECL_EXPORT
    #else
    #  define GNOME_EXPORT Q_DECL_IMPORT
    #endif

    typedef void (*ArrayToSceneFunction)(QVector<int>, QSet<int>, QSet<int>, unsigned, unsigned, unsigned);

    GNOME_EXPORT void sort(QVector<int> &data, ArrayToSceneFunction callback, unsigned & delay, bool &pause, bool &abort);

}


#endif // GNOME_H
