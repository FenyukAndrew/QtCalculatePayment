#ifndef COUNTER_TYPE_H
#define COUNTER_TYPE_H

enum e_input_or_edit {e_dlg_new_input=1,e_dlg_edit_value=2};

struct Counter_Type
{
    Counter_Type(const QString new_name,const double new_value) : name(new_name), value(new_value) {}
    const QString name;
    //const double last_value;
    const double value;
};

#endif // COUNTER_TYPE_H
