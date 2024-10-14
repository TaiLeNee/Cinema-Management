#ifndef MOVIE_H
#define MOVIE_H
#include <Datetime.h>
#include <string>

using namespace std;    
class Movie {
public:
    Movie(const wstring& name, const wstring& genre, Datetime duration, Datetime timeline, const wstring& description, const wstring& language, int age);   // hiển thị hên màn hình, tự set id
    Movie(int id, const wstring& name, const wstring& genre, Datetime duration, Datetime timeline, const wstring& description, const wstring& language, int age);   // hiển thị trong file
    void displayInfo() const;  // hiển thị thông tin phim
    void setId(int id);
    int getId() const;
    wstring getName() const;
    wstring getGenre() const;
    Datetime getDuration() const;
    Datetime getTimeline() const;
    wstring getDescription() const;
    wstring getLanguage() const;
    int getAge() const;

    void addInfoBefore();   // chèn 1 phim
    void addInfoAfter();
    void editInfo();   // chỉnh sửa phim


private:
    int id;
    wstring name;
    wstring genre;   // thể loại
    Datetime duration; // thời lượng
    Datetime timeline;  // khung giờ chiếu
    wstring description; // mô tả 
    wstring language;   // ngôn ngữ
    int age;  // độ tuổi 
};

#endif // MOVIE_H
