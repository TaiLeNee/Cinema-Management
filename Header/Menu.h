#ifndef MENU_H
#define MENU_H
#include "../Header/drawTable.h"
#include "../Header/TicketList.h"
#include "../Header/EmployeeList.h"
#include "../Header/CustomerList.h"
#include "../Header/drawTable.h"
#include "../Header/gotoXY.h"
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

void loginMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList);

void employeeMenu(ListOfEmployee &employeeList);

void movieMenu(MovieList &movieList);

void customerMenu(CustomerList &customerList);

void managementMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList);

// void manageMenu(RoomList &roomList, MovieList &movieList);
void mainMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, int typeEmployee);
void SellTicketInWeek(MovieList &movieList);
void manageShowtimes(RoomList &roomList, MovieList &movieList);




#endif // MENU_H    