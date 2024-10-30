#include "../Header/checkInput.h"

void checkInput(int &choice) {
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

}

