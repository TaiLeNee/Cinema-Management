#ifndef DRAWCALENDAR_H
#define DRAWCALENDAR_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <locale>
#include <codecvt>
#include "drawTable.h"
#include "Datetime.h"
#include "checkInput.h"

Datetime drawCalendar( int month, int year, int type);

#endif // DRAWCALENDAR_H