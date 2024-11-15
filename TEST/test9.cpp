#include <iostream>
#include <unistd.h> // Thư viện cho sleep() nếu cần

int main() {
    system("cls");
    std::cout << "Vi du minh hoa ne nha cac ban hien oi";
    std::cout<<"\n đây la dong thu 2 ne nha ca ban hien ơiiiiiiiiiiiiiiiiiiiiiii";
    std::cout.flush(); // Đảm bảo nội dung được hiển thị ngay lập tức
    
    sleep(2); // Đợi 2 giây để bạn quan sát
    
    // Di chuyển con trỏ đến một vị trí (nếu cần)
    std::cout << "\033[0;5H"; // Di chuyển con trỏ đến hàng thứ 2, cột 1
    
    // Xóa từ con trỏ đến cuối dòng
    std::cout << "\033[0J";
    std::cout.flush(); // Đảm bảo hành động được thực hiện ngay

    return 0;
}
