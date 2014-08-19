#include "Common_Struct_data.h"

//Region Electricity
void Electricity_record::Init()
{
    //Всегда нужно инициализировать, чтобы не было левых значений (по умолчанию ниинициализированы)
    Date_Input_Value=QDateTime();
    Last_Value_Day=0;
    Value_Day=0;
    Last_Value_Night=0;
    Value_Night=0;
    Value_External=0;
    delta_devices=0;
    Sum=0;
    Date_Payment=QDateTime();
    TariffDay=0;
    TariffNight=0;
    TariffCommon=0;
    Month_Year_Payment=QDate();
    Savings=0;
}

/*void Electricity_record::Set_Tariffs()
{

}*/

void Electricity_record::Calculate_Sum_and_Saving()
{
    Sum=TariffDay*(Value_Day-Last_Value_Day)+TariffNight*(Value_Night-Last_Value_Night);

    //Расчет экономии из-за использования 2-тарифного счетчика
    Savings=TariffCommon*(Value_Day-Last_Value_Day+Value_Night-Last_Value_Night)-Sum;
    //(НОВЫЙ_ДЕНЬ-СТАРЫЙ_ДЕНЬ)*ТАРИФ_ДЕНЬ+(НОВЫЙ_НОЧЬ-СТАРЫЙ_НОЧЬ)*ТАРИФ_НОЧЬ
    //-((НОВЫЙ_ДЕНЬ-СТАРЫЙ_ДЕНЬ)+(НОВЫЙ_НОЧЬ-СТАРЫЙ_НОЧЬ))*ТАРИФ_ОБЩИЙ
}


void Electricity_record::Calculate_delta_devices(int value_External_last_month)
{
    delta_devices=(Value_Day+Value_Night-Value_External)-(Last_Value_Day+Last_Value_Night-value_External_last_month);
    //Разница в показаниях счетчиков: двухтарифный и входной
    //Лучше считать с начальным месяцем в базе, но для этого нужно делать дополнительный запрос
}

//End Region Electricity
