#ifndef TARIFFSDB_H
#define TARIFFSDB_H

#include "commondb.h"

class TariffsDB : public CommonDB
{
public:
    TariffsDB();

    bool create_cursor();
    bool get_next_record(QString& name,double& tariff);
    void update_new_record(QString& name,double& tariff);

private:
};

#endif // TARIFFSDB_H
