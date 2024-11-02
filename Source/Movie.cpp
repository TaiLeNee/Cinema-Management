#include "../Header/Movie.h"
#include "../Header/LoveMovie.h"
#include "../Header/AnimatedMovie.h"
#include "../Header/ActionMovie.h"
#include "../Header/HorrorMovie.h"
#include <algorithm>
#include "../Header/checkInput.h"
using namespace std;


//Khai báo thêm hàm//////////////
time_t wstringToTime(const wstring& dateTimeStr) {
    struct tm tm {};
    wistringstream ss(dateTimeStr);
    ss >> get_time(&tm, L"%H:%M %d/%m/%Y");
    return mktime(&tm); // Chuyển sang time_t
}

int Movie::currentID = 0;


void sortShowtimes(vector<Showtime>& showtimes) {

    sort(showtimes.begin(), showtimes.end(), [](const Showtime& a, const Showtime& b) {
        return wstringToTime(a.getStartTime().getFulltime()) < wstringToTime(b.getStartTime().getFulltime());
    });


}


////////////////////////// Movie class implementation //////////////////////////

Movie::Movie() {}

Movie::Movie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    : id(id), name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {
    currentID = max(currentID, id);
    }

Movie::Movie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    :id(++currentID), name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {}

void Movie::addShowtime(const Showtime& showtime) {
    showtimes.push_back(showtime);
}

void Movie::displayShowtimes() const {
    vector<Showtime> showtimes = this->showtimes;
    sortShowtimes(showtimes);

    vector<vector<wstring>> table;
    table.push_back({L" Giờ chiếu ", L" Ngày chiếu "});
    
    
    for(auto &showtime: showtimes){
        Datetime startime = showtime.getStartTime();
        
        table.push_back({startime.getHour() + L":" + startime.getMinute(), 
                          startime.getDay() + L"/" + startime.getMonth() + L"/" + startime.getYear()});
    }
    drawTable(table);
}

void Movie::displayShowtimeInDay(const wstring& date) const {
    vector<Showtime> showtimes = this->showtimes;
    sortShowtimes(showtimes);

    vector<vector<wstring>> table;
    table.push_back({L"ID", L" Giờ chiếu ", L" Ngày chiếu "});
    
    for(auto &showtime: showtimes){
        Datetime startime = showtime.getStartTime();
        if(startime.getDate() == date){
            table.push_back({to_wstring(showtime.showtimeID), startime.getHour() + L":" + startime.getMinute(), 
                          startime.getDay() + L"/" + startime.getMonth() + L"/" + startime.getYear()});
        }
    }
    drawTable(table);
}


vector<Showtime>& Movie::getShowtimes()
{
    return this->showtimes;
}

void Movie::inputMovieInfo() {
    this->id = ++currentID;
    wcout << L"Nhập tên phim: ";
    getline(wcin, name);

    wcout << L"Nhập thời lượng phim (phút): ";
    wcin >> duration;

    wcin.ignore();
    wcout << L"Nhập mô tả phim: ";
    getline(wcin, description);

    wcout << L"Nhập quốc gia sản xuất: ";
    getline(wcin, country);

    wcout << L"Nhập phụ đề: ";
    getline(wcin, subTitle);

    wcout << L"Nhập giới hạn tuổi: ";
    wcin >> limitAge;
}


void Movie::displayInfo() const {
    vector<vector<wstring>> table;
    table.push_back({L"Thông tin phim"});
    table.push_back({L"ID: " + to_wstring(id)});
    table.push_back({L"Tên phim: " + name});
    table.push_back({L"Thời lượng: " + to_wstring(duration) + L" phút"});
    table.push_back({L"Mô tả: " + description});
    table.push_back({L"Quốc gia: " + country});
    table.push_back({L"Phụ đề: " + subTitle});
    table.push_back({L"Độ tuổi: " + to_wstring(limitAge)});
    drawTable(table);
}

void Movie::deleteInfo() {
    name = L"";
    duration = 0;
    description = L"";
    showtimes.clear();
    limitAge = 0;
    country = L"";
    subTitle = L"";
}



void Movie::editInfo() {
    int choice;
    wstring newName, newGenre, newDescription;
    int newDuration;

    do {
        // Hiển thị thông tin phim trước khi chỉnh sửa
        displayInfo();

        // Hiển thị menu chỉnh sửa
        vector<vector<wstring>> table;
        table.push_back({L"   Menu chỉnh sửa thông tin phim"});
        table.push_back({L"1. Sửa tên phim"});
        table.push_back({L"2. Sửa thời lượng phim"});
        table.push_back({L"3. Sửa mô tả phim"});
        table.push_back({L"4. Sửa quốc gia sản xuất"});
        table.push_back({L"5. Sửa phụ đề"});
        table.push_back({L"6. Sửa giới hạn tuổi"});
        table.push_back({L"0. Thoát chỉnh sửa"});
        drawTable(table);
        checkInput(L"Nhập lựa chọn:", choice);

        switch (choice) {
            case 1:
                wcout << L"Nhập tên mới: ";
                wcin.ignore();
                getline(wcin, newName);
                name = newName;
                // system("cls");
                break;
            case 2:
                wcout << L"Nhập thời lượng mới: ";
                wcin >> newDuration;
                duration = newDuration;
                system("cls");
                break;
            case 3:
                wcout << L"Nhập mô tả mới: ";
                wcin.ignore();
                getline(wcin, newDescription);
                description = newDescription;
                system("cls");
                break;
            case 4:
                wcout << L"Nhập quốc gia mới: ";
                wcin.ignore();
                getline(wcin, newGenre);
                country = newGenre;
                system("cls");
                break;
            case 5:
                wcout << L"Nhập phụ đề mới: ";
                wcin.ignore();
                getline(wcin, newGenre);
                subTitle = newGenre;
                system("cls");
                break;
            case 6:
                wcout << L"Nhập giới hạn tuổi mới: ";
                wcin >> limitAge;
                system("cls");
                break;
            case 0:
                wcout << L"Thoát chỉnh sửa." << endl;
                system("cls");
                return;
            default:
                wcout << L"Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
        }
    } while (choice != 5);
}

void Movie::setId(int id) {
    this->id = id;
}   

int Movie::getId() const {
    return id;
}

void Movie::setName(const wstring& name) {
    this->name = name;
}
wstring Movie::getName() const {
    return name;
}

void Movie::setDuration(int duration)
{
    this->duration = duration;
}

int Movie::getDuration() const {

    return duration;
}

void Movie::setSubTitle(const wstring &subTitle)
{
    this->subTitle = subTitle;
}

 wstring Movie::getSubTitle() const
{
    return subTitle;
}

void Movie::setCountry(const wstring &country)
{
    this->country = country;
}

wstring Movie::getCountry() const
{
    return country;
}

void Movie::setLimitAge(int limitAge)
{
    this->limitAge = limitAge;
}

int Movie::getLimitAge() const
{
    return limitAge;
}

void Movie::setDescription(const wstring &description)
{
    this->description = description;
}

wstring Movie::getDescription() const
{
    return description;
}

void Movie::deleteShowtime(int showtimeID) {
    showtimes.erase(remove_if(showtimes.begin(), showtimes.end(), [showtimeID](const Showtime& showtime) {
        return showtime.showtimeID == showtimeID;
    }), showtimes.end());
}

