#include "../Header/BookedList.h"


BookedList::BookedList() {}

void BookedList::addBooked(const Booked &booked) {
    bookedList.push_back(booked);
}

void BookedList::removeBooked(size_t index) {
    bookedList.erase(bookedList.begin() + index);
}

void BookedList::loadChairbookedFromCSV(const string& filename = "../DATA/payments.csv")
{   
    bookedList.clear();
    wifstream file(filename);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open())
    {
        wcerr << L"Không thể mở file payments.csv!" << endl;
        return;
    }

    wstring line;
    getline(file, line); // bỏ qua tiêu đề
    while (getline(file, line))
    {
        wstringstream ss;
        ss.str(line);
        wstring showtimeID, chairName, isBooked, ticketID, tmpID, employeeID, datetime, totalMoney;
        getline(ss, tmpID, L',');
        getline(ss, ticketID, L',');
        getline(ss, showtimeID, L',');
        getline(ss, employeeID, L',');
        getline(ss, datetime, L',');
        getline(ss, totalMoney, L',');

        //Xử lý đọc tên ghế từ file
        vector<wstring> chairNames;
        wstring tmpName;
        wstringstream ss1;
        getline(ss, tmpName);
        ss1.str(tmpName);

        getline(ss1, chairName, L'"');
        while (getline(ss1, chairName, L','))
        {
            // Loại bỏ khoảng trắng đầu và cuối chuỗi
            chairName.erase(0, chairName.find_first_not_of(L"\" \t"));
            chairName.erase(chairName.find_last_not_of(L" \t\"") + 1);
            chairNames.push_back(chairName);
        }

        addBooked(Booked(stoi(tmpID), stoi(ticketID), stoi(showtimeID), stoi(employeeID), datetime, totalMoney, chairNames));
    }
    file.close();
}
// Booked BookedList::getBooked(size_t index) const {
//     return bookedList[index];
// }

size_t BookedList::getBookedCount() const {
    return bookedList.size();
}

void BookedList::clear() {
    bookedList.clear();
}   

void BookedList::displayBooked() const {
    vector<vector<wstring>> table;
    table.push_back({L"ID", L"Showtime ID", L"Ticket ID", L"Employee ID", L"Datetime", L"Total Money", L"Chair Names"});
    for (size_t i = 0; i < bookedList.size(); ++i) {
        Booked booked = bookedList[i];
        vector<wstring> row;
        row.push_back(to_wstring(i));
        row.push_back(to_wstring(booked.getShowtimeID()));
        row.push_back(to_wstring(booked.getTicketID()));
        row.push_back(to_wstring(booked.getEmployeeID()));
        row.push_back(booked.getDatetime());
        row.push_back(booked.getTotalMoney());
        wstring chairNames;
        for (size_t j = 0; j < booked.getChairNames().size(); ++j) {
            chairNames += booked.getChairNames()[j];
            if (j != booked.getChairNames().size() - 1) {
                chairNames += L", ";
            }
        }
        row.push_back(chairNames);
        table.push_back(row);
    }
    drawTable(table);
}


vector<Booked> &BookedList::getBooked() {
    return bookedList;
}
// #include "../Header/Booked.h"