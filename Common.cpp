#include "Common.h"

#include <QtGlobal>

#ifdef Q_OS_ANDROID
//Для Android версии
    const char* pathDB="/mnt/sdcard/sdcard2/Payments.db";
#endif

#ifdef Q_OS_LINUX
const char* pathDB="/home/andrew/Dropbox/OutWiker_Files/Databases/Payments.db";
#endif

#ifdef Q_OS_WIN32
#endif

//Можно описывать в файле .pro
/*Why don't you use the "else" keyword ?
android {
  SOURCES += androidStuff.cpp

} else: win32 {
  SOURCES += w32Stuff.cpp
}*/
