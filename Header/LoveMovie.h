#include "Movie.h"

using namespace std;

class LoveMovie : public Movie {
    public:
        LoveMovie();

        LoveMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic);

        LoveMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic);
       
        LoveMovie(const Movie& movie);
        //Hàm ảo từ lớp cha
        void inputMovieInfo();
        void displayInfo() const;
        void deleteInfo();
        void editInfo();    

        void setRomantic(const wstring& romantic);
        wstring getRomantic() const;

    private:
        wstring romantic; // Loại phim tình cảm
};