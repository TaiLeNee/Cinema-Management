#ifndef BOOKEDLIST_H
#define BOOKEDLIST_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "Booked.h"

class BookedList {
private:
    std::vector<Booked> bookedList;

public:
    // Constructor
    BookedList();

    // Add a booked item to the list
    void addBooked(const Booked& booked);

    // Remove a booked item from the list by index
    void removeBooked(size_t index);

    // Load booked items from file
    void loadChairbookedFromCSV(const string& filename);


    // Get a booked item by index
    // Booked getBooked(size_t index) const;

    vector<Booked> &getBooked();

    // Get the total number of booked items
    size_t getBookedCount() const;

    // Clear all booked items
    void clear();

    void displayBooked() const;

    
};

#endif // BOOKEDLIST_H