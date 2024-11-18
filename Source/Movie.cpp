#include "../Header/Movie.h"
#include "../Header/LoveMovie.h"
#include "../Header/AnimatedMovie.h"
#include "../Header/ActionMovie.h"
#include "../Header/HorrorMovie.h"
#include <algorithm>
#include "../Header/checkInput.h"
#include <conio.h>

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
    vector<wstring> movieInfo(6);
    vector<wstring> labels = {
        L"Tên phim: ",
        L"Thời lượng (phút): ",
        L"Phụ đề: ",
        L"Quốc gia: ",
        L"Độ tuổi: ",
        L"Mô tả: "
    };

    int currentField = 0;
    wchar_t temp;

    while (true) {
        system("cls");

        // Tạo bảng với các nhãn và giá trị hiện tại
        vector<vector<wstring>> table;
        drawTable({{L"Nhập thông tin phim"}});

        for (int i = 0; i < labels.size(); ++i) {
            if (i == currentField) {
                table.push_back({L"» " + labels[i], movieInfo[i]});
            } else {
                table.push_back({L"  " + labels[i], movieInfo[i]});
            }
        }

        // Vẽ bảng
        drawTable(table);

        temp = _getwch();

        if (temp == '\r') { // Enter key
            if (currentField == 5) break; // Finish input if on the last field
            currentField++;
        } else if (temp == 224 || temp == 0) { // Arrow keys
            temp = _getwch();
            if (temp == 72) { // Up arrow
                currentField = (currentField == 0) ? 5 : currentField - 1;
            } else if (temp == 80) { // Down arrow
                currentField = (currentField == 5) ? 0 : currentField + 1;
            }
        } else if (temp == '\b') { // Backspace key
            if (!movieInfo[currentField].empty()) {
                movieInfo[currentField].pop_back();
            }
        } else if (temp >= 32 && temp <= 126) { // Printable characters
            movieInfo[currentField] += temp;
        } else if (temp >= 128) { // Unicode characters
            movieInfo[currentField] += temp;
        }
    }

    // Assign the collected information to the movie object
    try{
        this->id = ++currentID;
        this->name = movieInfo[0];
        this->duration = stoi(movieInfo[1]);
        this->subTitle = movieInfo[2];
        this->country = movieInfo[3];
        this->limitAge = stoi(movieInfo[4]);
        this->description = movieInfo[5];}
    catch(exception& e){
        red(L"[Lỗi nhập dữ liệu. Vui lòng kiểm tra lại.]\n");
        --currentID;
        system("pause");
        inputMovieInfo();
    }
}


void Movie::displayInfo() {
    // drawTable({
    //     {L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia", L"Độ tuổi", L"Mô tả"},
    //     {to_wstring(getId()), getName(), to_wstring(getDuration()), getSubTitle(), getCountry(), to_wstring(getLimitAge()), actionLevel, getDescription()}
    // });
    // wcout<<L"test\n";
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
        system("cls");
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
            case 1:{
            inputName:
                yellow(L"Nhập tên mới: ");
                wcin.ignore();
                getline(wcin, newName);

                if(newName == L"" || newName == L"\n"){
                    red(L"[Tên phim không được để trống.]\n");
                    newName.clear();    
                    goto inputName;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setName(newName);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    name = newName;
                    system("cls");
                    green(L"[Đã cập nhật tên phim thành công.]\n");
                    this->displayInfo();
                }

                break;
            }
            case 2:{
                inputDuration:
                yellow(L"Nhập thời lượng mới: ");
                wcin >> newDuration;

                if(newDuration <= 0){
                    red(L"[Thời lượng phim không hợp lệ.]\n");
                    goto inputDuration;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setDuration(newDuration);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    duration = newDuration;
                    system("cls");
                    green(L"[Đã cập nhật thời lượng phim thành công.]\n");
                    this->displayInfo();
                }

                break;
            }

            case 3:{
                inputDescription:
                yellow(L"Nhập mô tả mới: ");
                wcin.ignore();
                getline(wcin, newDescription);

                if(newDescription == L"" || newDescription == L"\n"){
                    red(L"[Mô tả phim không được để trống.]\n");
                    newDescription.clear();
                    goto inputDescription;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setDescription(newDescription);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    description = newDescription;
                    system("cls");
                    green(L"[Đã cập nhật mô tả phim thành công.]\n");
                    this->displayInfo();
                }

                break;
            }

            case 4:{
                inputCountry:
                wstring newCountry;
                yellow(L"Nhập quốc gia sản xuất mới: ");
                wcin.ignore();
                getline(wcin, newCountry);

                if(newCountry == L"" || newCountry == L"\n"){
                    red(L"[Quốc gia sản xuất không được để trống.]\n");
                    newCountry.clear();
                    goto inputCountry;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setCountry(newCountry);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    country = newCountry;
                    system("cls");
                    green(L"[Đã cập nhật quốc gia sản xuất thành công.]\n");
                    this->displayInfo();
                }

                break;
            }

            case 5:{

                inputSubTitle:
                wstring newSubTitle;
                yellow(L"Nhập phụ đề mới: ");
                wcin.ignore();
                getline(wcin, newSubTitle);

                if(newSubTitle == L"" || newSubTitle == L"\n"){
                    red(L"[Phụ đề không được để trống.]\n");
                    goto inputSubTitle;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setSubTitle(newSubTitle);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    subTitle = newSubTitle;
                    system("cls");
                    green(L"[Đã cập nhật phụ đề thành công.]\n");
                    this->displayInfo();
                }

                break;
            }

            case 6:{
                inputLimitAge:
                int newLimitAge;
                yellow(L"Nhập giới hạn tuổi mới: ");
                wcin >> newLimitAge;

                if(newLimitAge <= 0){
                    red(L"[Giới hạn tuổi không hợp lệ.]\n");
                    goto inputLimitAge;
                }

                Movie* tmp = this;
                system("cls");
                tmp->setLimitAge(newLimitAge);
                tmp->displayInfo();
                wchar_t c;
                green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                wcin >> c;
                c = towlower(c);
                if(c == 'y'){
                    limitAge = newLimitAge;
                    system("cls");
                    green(L"[Đã cập nhật giới hạn tuổi thành công.]\n");
                    this->displayInfo();
                }

                break;
            }   

            case 0:
                break;  
        }
    } while (choice != 0);
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

void Movie::resetShowtimes() {
    showtimes.clear();
}

