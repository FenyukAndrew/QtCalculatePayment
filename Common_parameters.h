#ifndef COMMON_PARAMETERS_H
#define COMMON_PARAMETERS_H

constexpr double c_percent_Sberbank=1+0.01;//Комиссия Сбербанка 1%

constexpr char c_types_of_payments=4;//4 вида коммунальных платежей

constexpr int C_TIME_FROM_PAYMENT=60*60*12;//Оплата была произведена в течении последних 12 часов;
//#define C_TIME_FROM_PAYMENT 60*60*12

//constexpr char* c_format_Date_Input_Value="dd.MM.yyyy hh:mm:ss";
constexpr char* c_format_Date_Input_Value="dd.MM.yyyy hh:mm";
constexpr char* c_format_Date_checkBox_HavePaid="dd.MM.yyyy hh:mm:ss";
constexpr char* c_format_Date_Month_Year_Payment="MM\\yyyy";

#include <QLocale>

//static QLocale system_locale(QLocale::Russian);
static QLocale system_locale(QLocale::system());

#ifdef Q_OS_ANDROID
//Для Android версии все окна выводяться на весь экран
#define ANDROID_MAKE_WINDOW_FULL_SCREEN setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#else
#define ANDROID_MAKE_WINDOW_FULL_SCREEN
#endif

#endif // COMMON_PARAMETERS_H
