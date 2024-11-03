#include <iostream>
#include <windows.h>

void loading(int duration) {
    const int numDots = 3;
    for (int i = 0; i < duration; ++i) {
        system("cls");
        std::cout << "\rLoading";
        for (int j = 0; j < i % (numDots + 1); ++j) {
            std::cout << ".";
        }
        std::cout << std::flush;
        Sleep(500);
    }
    std::cout << "\rLoading complete!" << std::endl;
}


#include <iostream>
#include <windows.h>

void countdown(int seconds) {
    for (int i = seconds; i >= 0; --i) {
        std::cout << "\rCounting down: " << i << " seconds remaining" << std::flush;
        
        // Tạm dừng 1 giây
        Sleep(1000);
        std::cout << fflush;
    }
    std::cout << "\rCountdown complete!" << std::endl;
}


int main() {
    int duration = 10; // Thời gian thực hiện hiệu ứng (số lần lặp)
    loading(duration);
     int seconds = 10; // Số giây đếm ngược
    countdown(seconds);
    return 0;
}
