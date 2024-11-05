#ifndef MENU_H
#define MENU_H
#include "EmployeeList.h"
#include "CustomerList.h"
#include "gotoXY.h"
#include "checkInput.h"
#include <cstdlib>
#include <iostream>
#include "Color.h"
#include "MovieList.h"
#include "RoomList.h"
#include "drawTable.h"
#include "TicketList.h"
#include <string>
#include <vector>
#include <regex>
#include "drawCalendar.h"

void loginMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList);

void employeeMenu(ListOfEmployee &employeeList);

void movieMenu(MovieList &movieList);

void customerMenu(CustomerList &customerList);

void managementMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList);

// void manageMenu(RoomList &roomList, MovieList &movieList);
void mainMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList, int typeEmployee);

void SellTicketInWeek(MovieList &movieList);
void manageShowtimes(RoomList &roomList, MovieList &movieList);
void statisticMenu(MovieList &movieList, RoomList &roomList, CustomerList &customerList, ListOfEmployee &employeeList, BookedList &bookedList);

void statisticRevenue(MovieList &movieList, ListOfEmployee &employeeList, BookedList &bookedList);



#endif // MENU_H    