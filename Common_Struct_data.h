#ifndef COMMON_STRUCT_DATA_H
#define COMMON_STRUCT_DATA_H

#include <QDate>

struct Water_record
{
    QDateTime Date_Input_Value;
    int Value;//Только целые, т.к. оплата производиться только по целым значениям
    //double last_Value;
    double Sum;
    double Sum_Commission;
    QDateTime Date_Payment;
    double Tariff;
    QDate Month_Year_Payment;

    Water_record()
    {
        Init();
    }

    inline void Init()
    {
        Date_Input_Value=QDateTime();
        Value=0;
        //last_Value=0;
        Sum=0;
        Sum_Commission=0;
        Date_Payment=QDateTime();
        Tariff=0;
        Month_Year_Payment=QDate();
    }
};

struct Electricity_record
{
    QDateTime Date_Input_Value;
    int Last_Value_Day;
    int Value_Day;
    int Last_Value_Night;
    int Value_Night;
    int Value_External;
    int delta_devices;//Разница в показаниях счетчиков: двухтарифный и входной
    //Только целые, т.к. оплата производиться только по целым значениям
    double Sum;
    QDateTime Date_Payment;
    double TariffDay;
    double TariffNight;
    double TariffCommon;
    QDate Month_Year_Payment;
    double Savings;

    Electricity_record()
    {
        Init();
    }

    void Init();
    void Calculate_Sum_and_Saving();
    void Calculate_delta_devices(int value_External_last_month);
};

struct Gas_record
{
    QDateTime Date_Input_Value;
    int Value;
    //Только целые, т.к. оплата производиться только по целым значениям
    double Sum;
    QDateTime Date_Payment;
    double Tariff;
    QDate Month_Year_Payment;

    Gas_record()
    {
        Init();
    }

    inline void Init()
    {
        Date_Input_Value=QDateTime();
        Value=0;
        Sum=0;
        Date_Payment=QDateTime();
        Tariff=0;
        Month_Year_Payment=QDate();
    }
};

struct Rubbish_record
{
    QDateTime Date_Input_Value;
    double Sum;
    QDateTime Date_Payment;
    QDate Month_Year_Payment;

    Rubbish_record()
    {
        Init();
    }

    inline void Init()
    {
        Date_Input_Value=QDateTime();
        Sum=0;
        Date_Payment=QDateTime();
        Month_Year_Payment=QDate();
    }
};

#endif // COMMON_STRUCT_DATA_H
