#include "Common.h"

#include <QtGlobal>

#ifdef Q_OS_ANDROID
//Для Android версии
const char* pathDB="/mnt/sdcard/sdcard2/Payments.db";
//const char* pathDB="/mnt/sdcard/Payments.db";//Для 1 SD Card

//Т.к. Android принадлежит множеству Linux
#elif defined(Q_OS_LINUX)
//const char* pathDB="/home/andrew/Dropbox/OutWiker_Files/Databases/Payments.db";
const char* pathDB="/home/andrew/DISK_sdb/Dropbox/Dropbox/OutWiker_Files/Databases/Payments.db";
#endif

#ifdef Q_OS_WIN32
const char* pathDB="C:/Dropbox/OutWiker_Files/Databases/Payments.db";
#endif

//Можно описывать в файле .pro
/*Why don't you use the "else" keyword ?
android {
  SOURCES += androidStuff.cpp

} else: win32 {
  SOURCES += w32Stuff.cpp
}*/
