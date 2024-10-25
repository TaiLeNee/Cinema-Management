#ifndef MENU_H
#define MENU_H

#include <cstdlib>
#include <iostream>
#include "Color.h"
#include "MovieList.h"
#include <string>

void manageMenu();
void mainMenu(MovieList &movieList);
void sellTicketMenu(MovieList &movieList);

#endif // MENU_H    