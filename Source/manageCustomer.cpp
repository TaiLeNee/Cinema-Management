#include "../Header/Menu.h"

void SubMenuEdit(CustomerList& customerList, Customer* customer){
    Position pos = getXY();
    int x = pos.X;
    int y = pos.Y;

editMenu:
    gotoXY(x, y);
    wcout<<L"\033[0J";
    drawTable({
        {L"1. Chỉnh sửa thông tin"},
        {L"2. Xóa khách hàng"},
        {L"0. Quay lại"}
    });


    int choice;
    checkInput(L"Nhập lựa chọn", choice);

    switch (choice){
        case 1:
            system("cls");
            customerList.editCustomer(customer->getCustomerID());
            break;
        case 2:
            system("cls");
            customerList.deleteCustomer(customer->getCustomerID());
            break;
        case 0:
            return;
        default:
            red(L"Lựa chọn không hợp lệ. Vui lòng thử lại.");
    }

    goto editMenu;

}

void customerMenu(CustomerList &customerList)
{
    int choice;
    do
    {   system("cls");
        vector<vector<wstring>> table;
        table.push_back({L"    Menu Quản lý Khách hàng "});
        table.push_back({L"1. Hiện thị danh sách khách hàng"});
        table.push_back({L"2. Tìm kiếm khách hàng"});
        table.push_back({L"3. Thêm khách hàng"});
        table.push_back({L"0. Quay lại"});

        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:{
            customerList.displayCustomers();
            int choiceCustomer;
            red(L"Nhập 0: quay lại.\n");

            Position pos = getXY();
            int x = pos.X;
            int y = pos.Y;
        inputID:
            gotoXY(0, y);
            checkInput(L"Nhập ID khách hàng cần tương tác", choiceCustomer);
            wcout<<L"\033[0J";

            if(choiceCustomer == 0){
                system("cls");
                break;
            }
            Customer* customer = customerList.findCustomerID(choiceCustomer);
            if(customer){
                system("cls");
                drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
                customer->displayInfo();
                SubMenuEdit(customerList, customer);
            }else{
                red(L"Không tìm thấy khách hàng có ID = " + to_wstring(choiceCustomer) + L"\n");
                gotoXY(39, y);
                wcout << L"                                 ";
                
                goto inputID;
            }
            break;
        }
        case 2:{
            wstring searchCustomer;
            wcin.ignore();
            system("cls");
            red(L"Nhập 0: quay lại.\n"); 
            drawTable({{L"Nhập ID/Tên/SĐT khách hàng cần tìm: ", L"                                                     "}});
            Position pos = getXY();
            int x = pos.X;
            int y = pos.Y;
        inputSearch:   
            gotoXY(52, y-2);
            wcout << L"                                                     ";
            gotoXY(52, y-2);
            getline(wcin, searchCustomer);
            if(searchCustomer == L"0"){
                system("cls");
                break;
            }

            Customer* customer = customerList.findCustomerAll(searchCustomer);
            if(customer){

                system("cls");
                drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
                customer->displayInfo();
                SubMenuEdit(customerList, customer);
            }else{
                red(L"Không tìm thấy khách hàng có thông tin: " + searchCustomer + L"\n");
                goto inputSearch;
            }
            break;

        }
        case 0:
            break;
        default:
            wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    } while (choice != 0);
}