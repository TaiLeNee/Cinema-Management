#include "../Header/checkInput.h"
#include <sstream>

void checkInput(wstring text, int &choice) {
   // Kiểm tra đầu vào của người dùng
        wstring input;
        while(1){
            wcout<<L"\033[92m══["<<text<<L"]══> \033[0m";
            wcin >> input ;
            wstringstream ss(input);

            if(!(ss>>choice)){
                wcout <<L"\033[91m"<< L"[Lựa chọn không hợp lệ. Vui lòng nhập lại.]"<<L"\033[0m" << endl;
                continue;
            }   
            return; 
        }
}
