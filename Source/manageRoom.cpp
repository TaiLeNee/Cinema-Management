#include "../Header/Menu.h"

void roomMenu(RoomList &roomList)
{
    int choice;
    do
    {
        system("cls");
        vector<vector<wstring>> table;
        table.push_back({L"    Menu Quản lý Phòng chiếu "});
        table.push_back({L"1. Hiện thị danh sách phòng chiếu"});
        table.push_back({L"2. Thêm phòng chiếu"});
        // table.push_back({L"3. Sửa phòng chiếu"});
        // table.push_back({L"4. Xóa phòng chiếu"});
        table.push_back({L"0. Quay lại"});

        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:{
            roomList.displayRooms();
            int choiceRoom;
            red(L"Nhập 0: quay lại.\n");
            checkInput(L"Nhập ID phòng cần tương tác", choiceRoom);
            if(choiceRoom == 0){
                system("cls");
                break;
            }

            for(auto &room: roomList.getRooms()){
                if(room.getId() == choiceRoom){
                    room.displayInfo();
                    drawTable({
                        {L"1. Sửa tên phòng"},
                        {L"2. Sửa số hàng ghế"},
                        {L"3. Sửa số ghế mỗi hàng"},    
                        {L"4. Sửa màn hình"},
                        {L"5. Sửa trạng thái"},
                        {L"0. Quay lại"}
                    });
                    int choice;
                    checkInput(L"Nhập lựa chọn", choice);
                    wcin.ignore();
                    switch (choice){
                        case 1:{
                            wstring name;
                            wcout << L"Nhập tên phòng: ";
                            getline(wcin, name);

                            Room tmp = room;
                            tmp.setName(name);
                            tmp.displayInfo();
                            wchar_t c;
                            green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                            wcin >> c;
                            c = towlower(c);
                            if(c == 'y'){
                                room.setName(name);
                                green(L"══[Đã lưu chỉnh sửa]══.\n");
                            }
                            else{
                                red(L"[Hủy bỏ chỉnh sửa].\n");
                                Sleep(1000);
                            }
                            break;
                        }
                        case 2:{
                            int numRows;
                            checkInput(L"Nhập số hàng ghế", numRows);
                            Room tmp = room;
                            tmp.setNumRows(numRows);
                            tmp.displayInfo();
                            wchar_t c;
                            green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                            wcin >> c;
                            c = towlower(c);
                            if(c == 'y'){
                                room.setNumRows(numRows);
                                green(L"══[Đã lưu chỉnh sửa]══.\n");
                            }
                            else{
                                red(L"[Hủy bỏ chỉnh sửa].\n");
                                Sleep(1000);
                            }
    

                            break;
                        }
                        case 3:{
                            int numChairsPerRow;
                            checkInput(L"Nhập số ghế mỗi hàng", numChairsPerRow);
                            Room tmp = room;
                            tmp.setNumChairsPerRow(numChairsPerRow);
                            tmp.displayInfo();
                            wchar_t c;
                            green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                            wcin >> c;
                            c = towlower(c);
                            if(c == 'y'){
                                tmp.setNumChairsPerRow(numChairsPerRow);
                                green(L"══[Đã lưu chỉnh sửa]══.\n");
                            }
                            else{
                                red(L"[Hủy bỏ chỉnh sửa].\n");
                                Sleep(1000);
                            }
                            break;
                        }
                        case 4:{
                            wstring screen;
                            green(L"════[Nhập màn hình]==> ");
                            getline(wcin, screen);
                            Room tmp = room;
                            tmp.setScreen(screen);
                            tmp.displayInfo();
                            wchar_t c;
                            green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                            wcin >> c;
                            c = towlower(c);
                            if(c == 'y'){
                                tmp.setScreen(screen);
                                green(L"══[Đã lưu chỉnh sửa]══.\n");
                            }
                            else{
                                red(L"[Hủy bỏ chỉnh sửa].\n");
                                Sleep(1000);
                            }
                            break;
                        }

                        case 5:{
                            int status;
                            checkInput(L"Nhập trạng thái (1:Hoạt động, 0:Bảo trì)", status);
                            Room tmp = room;
                            tmp.setStatus(status);
                            tmp.displayInfo();
                            wchar_t c;
                            green(L"════[ Xác nhận lưu chỉnh sửa (y/n): ]==> ");
                            wcin >> c;
                            c = towlower(c);
                            if(c == 'y'){
                                tmp.setStatus(status);
                                green(L"══[Đã lưu chỉnh sửa]══.\n");
                            }
                            else{
                                red(L"[Hủy bỏ chỉnh sửa].\n");
                                Sleep(1000);
                            }
                            break;
                        }
                    }
                }
            }
            break;
        }
        case 2:{
            system("cls");
            roomList.addRoom();
            break;
        }
        case 0:
            return;
        default:
            red(L"Lựa chọn không hợp lệ. Vui lòng thử lại.");
        }
    } while (choice != 0);
}