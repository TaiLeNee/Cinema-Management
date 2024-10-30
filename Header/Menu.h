#ifndef MENU_H
#define MENU_H

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

void manageMenu(RoomList &roomList, MovieList &movieList);
void mainMenu(RoomList &roomList, MovieList &movieList);
void SellTicketInWeek(MovieList &movieList);
void manageShowtimes(RoomList &roomList, MovieList &movieList);


#endif // MENU_H    