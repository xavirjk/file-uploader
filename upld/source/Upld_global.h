#ifndef UPLD_GLOBAL_H
#define UPLD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPLD_LIBRARY)
#  define UPLD_EXPORT Q_DECL_EXPORT
#else
#  define UPLD_EXPORT Q_DECL_IMPORT
#endif

#endif // UPLD_GLOBAL_H
