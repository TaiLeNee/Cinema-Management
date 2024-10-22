#include "../Header/Movie.h"




using namespace std;

// Thiết lập chế độ Unicode cho console



Movie::Movie() {}

Movie::Movie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    : id(id), name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {}

Movie::Movie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description)
    : name(name), duration(duration), subTitle(subTitle), country(country), limitAge(limitAge), description(description) {}

void Movie::addShowtime(const Showtime& showtime) {
    showtimes.push_back(showtime);
}

void Movie::displayShowtimes() const {
    vector<vector<wstring>> table;
    table.push_back({L" Giờ chiếu ", L" Ngày chiếu "});
    
    
    for(auto &showtime: showtimes){
        Datetime startime = showtime.getStartTime();

        table.push_back({startime.getHour() + L":" + startime.getMinute(), 
                          startime.getDay() + L"/" + startime.getMonth() + L"/" + startime.getYear()});
    }
    drawTable(table);
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



    wcout << L"+--------------------------------------------------+" << endl;
    wcout << L"|                    Thông Tin Phim                |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Tên             | " << setw(30) << name.c_str() << L" |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Thời lượng      | " << setw(25) << duration << L" phút |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Mô tả           | " << setw(30) << description.c_str() << L" |" << endl;
    wcout << L"+--------------------------------------------------+" << endl;
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
                wcin.ignore();
                getline(wcin, newName);
                name = newName;
                break;
            case 2:
                wcout << L"Nhập thể loại mới: ";
                wcin.ignore();
                getline(wcin, newGenre);
                // genre = newGenre;
                break;
            case 3:
                wcout << L"Nhập thời lượng mới: ";
                wcin >> newDuration;
                duration = newDuration;
                break;
            case 4:
                wcout << L"Nhập mô tả mới: ";
                wcin.ignore();
                getline(wcin, newDescription);
                description = newDescription;
                break;
            case 5:
                wcout << L"Thoát chỉnh sửa." << endl;
                break;
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

