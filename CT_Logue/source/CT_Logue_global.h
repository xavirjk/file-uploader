#ifndef CT_LOGUE_GLOBAL_H
#define CT_LOGUE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CT_LOGUE_LIBRARY)
#  define CT_LOGUE_EXPORT Q_DECL_EXPORT
#else
#  define CT_LOGUE_EXPORT Q_DECL_IMPORT
#endif

#endif // CT_LOGUE_GLOBAL_H
