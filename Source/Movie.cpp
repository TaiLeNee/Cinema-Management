#include "../Header/Movie.h"
#include "../Header/LoveMovie.h"
#include "../Header/AnimatedMovie.h"
#include "../Header/ActionMovie.h"
#include "../Header/HorrorMovie.h"
#include <algorithm>
using namespace std;

//Khai báo thêm hàm//////////////
time_t wstringToTime(const wstring& dateTimeStr) {
    struct tm tm {};
    wistringstream ss(dateTimeStr);
    ss >> get_time(&tm, L"%H:%M %d/%m/%Y");
    return mktime(&tm); // Chuyển sang time_t
}


void sortShowtimes(vector<Showtime>& showtimes) {

    sort(showtimes.begin(), showtimes.end(), [](const Showtime& a, const Showtime& b) {
        return wstringToTime(a.getStartTime().getFulltime()) < wstringToTime(b.getStartTime().getFulltime());
    });


}


////////////////////////// Movie class implementation //////////////////////////

Movie::Movie() {}

Movie::Movie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    : id(id), name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {}

Movie::Movie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    : name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {}

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

vector<Showtime> Movie::getShowtimes() const
{
    return this->showtimes;
}

void Movie::inputMovieInfo() {
    wcout << L"Nhập tên phim: ";
    wcin.ignore();
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
    wcin.ignore();
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
        wcout << L"+----------------------------------------+" << endl;
        wcout << L"|           Chọn thông tin chỉnh sửa     |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
        wcout << L"| 1. Tên                                 |" << endl;
        wcout << L"| 2. Thể loại                            |" << endl;
        wcout << L"| 3. Thời lượng                          |" << endl;
        wcout << L"| 4. Mô tả                               |" << endl;
        wcout << L"| 5. Thoát                               |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
        wcout << L"Lựa chọn của bạn: ";
        // Kiểm tra đầu vào của người dùng
        bool validInput = false;
        while (!validInput) {
            wcout << L"Lựa chọn của bạn: ";
            wcin >> choice;

            if (wcin.fail()) {
                wcin.clear(); // Xóa trạng thái lỗi
                wcin.ignore(1e4, '\n'); // Xóa bộ nhớ đệm
                wcout << L"Lựa chọn không hợp lệ. Vui lòng nhập lại." << endl;
            } else {
                validInput = true;
                wcin.ignore();
            }
        }

        switch (choice) {
            case 1:
                wcout << L"Nhập tên mới: ";
                getline(wcin, newName);
                name = newName;
                system("cls");
                break;
            case 2:{
                vector<vector<wstring>> table;
                table.push_back({L"  Chọn Thể Loại Phim Muốn Đổi"});
                table.push_back({L"1. Tình cảm"});
                table.push_back({L"2. Hoạt hình"});
                table.push_back({L"3. Hành động"});
                table.push_back({L"4. Kinh dị"});
                table.push_back({L"0. Quay lại"});
                drawTable(table);
                wcout << L"\033[92m[Lựa chọn của bạn]  ";
                int choice;
                wcin >> choice;
                wcin.ignore();
                switch (choice){
                    case 1: {
                        // Tạo đối tượng LoveMovie mới và sao chép dữ liệu
                        LoveMovie* loveMovie = new LoveMovie(*this);
                        if (loveMovie) {
                            system("cls");
                            wcout << L"Đã chuyển đổi sang thể loại Tình cảm." << endl;
                            // Thay thế đối tượng hiện tại bằng đối tượng mới
                            *this = *loveMovie;
                            delete loveMovie;
                        } else {
                            wcout << L"Không thể chuyển đổi sang thể loại Tình cảm." << endl;
                        }
                        break;
                    }
                    case 2: {
                        // Tạo đối tượng AnimatedMovie mới và sao chép dữ liệu
                        AnimatedMovie* animatedMovie = new AnimatedMovie(*this);
                        if (animatedMovie) {
                            system("cls");
                            wcout << L"Đã chuyển đổi sang thể loại Hoạt hình." << endl;
                            // Thay thế đối tượng hiện tại bằng đối tượng mới
                            *this = *animatedMovie;
                            delete animatedMovie;
                            system("cls");
                        } else {
                            wcout << L"Không thể chuyển đổi sang thể loại Hoạt hình." << endl;
                        }
                        break;
                    }
                    case 3: {
                        // Tạo đối tượng ActionMovie mới và sao chép dữ liệu
                        ActionMovie* actionMovie = new ActionMovie(*this);
                        if (actionMovie) {
                            system("cls");
                            wcout << L"Đã chuyển đổi sang thể loại Hành động." << endl;
                            // Thay thế đối tượng hiện tại bằng đối tượng mới
                            *this = *actionMovie;
                            delete actionMovie;
                        } else {
                            wcout << L"Không thể chuyển đổi sang thể loại Hành động." << endl;
                        }
                        break;
                    }
                    case 4: {
                        // Tạo đối tượng HorrorMovie mới và sao chép dữ liệu
                        HorrorMovie* horrorMovie = new HorrorMovie(*this);
                        if (horrorMovie) {
                            system("cls");
                            wcout << L"Đã chuyển đổi sang thể loại Kinh dị." << endl;
                            // Thay thế đối tượng hiện tại bằng đối tượng mới
                            *this = *horrorMovie;
                            delete horrorMovie;
                        } else {
                            wcout << L"Không thể chuyển đổi sang thể loại Kinh dị." << endl;
                        }
                        break;
                    }
                    case 0:
                        system("cls");
                        break;
                    default:
                        wcout << L"Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
                        break;
                }
            }
                break;
            case 3:
                wcout << L"Nhập thời lượng mới: ";
                wcin >> newDuration;
                duration = newDuration;
                system("cls");
                break;
            case 4:
                wcout << L"Nhập mô tả mới: ";
                wcin.ignore();
                getline(wcin, newDescription);
                description = newDescription;
                system("cls");
                break;
            case 5:
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

