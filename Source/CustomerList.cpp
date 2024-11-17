#include "../Header/Customer.h"
#include "../Header/CustomerList.h"
#include "../Header/getXY.h"
#include "../Header/gotoXY.h"

using namespace std;

CustomerList::CustomerList() {
    // loadFromCSV("../DATA/customers.csv");
}

vector<Customer>& CustomerList::getCustomers(){
    return customers;
}

void CustomerList::addCustomer( const wstring& name, const wstring& phoneNumber, int point) {
    customers.push_back(Customer(name, phoneNumber, point));
}

void CustomerList::deleteCustomer(int id) {
    auto it = find_if(customers.begin(), customers.end(), [id](const Customer& customer) {
        return customer.getCustomerID() == id;
    });
    if (it != customers.end()) {
        drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
        it->displayInfo();
        wchar_t ct;
        green(L"Xác nhận xóa khách hàng? (y/n): ");
        wcin >> ct;
        ct = towlower(ct);  
        if(ct == 'y'){  

            customers.erase(it);
            green(L"═════[Xóa khách hàng thành công.]═════\n");
            saveToCSV("../DATA/customers.csv");
            Sleep(1000);
        }else{
            red(L"[Đã hủy xóa khách hàng.]\n");
        }
    }else {
        red(L"Không tìm thấy khách hàng có ID = " + to_wstring(id) + L"\n");
    }
}

void CustomerList::editCustomer(int id) {
    auto it = find_if(customers.begin(), customers.end(), [id](const Customer& customer) {
        return customer.getCustomerID() == id;
    });
   vector<vector<wstring>> table;
    wstring newName,newPhoneNumber;
    int newPoint;
edit:
    system("cls");
    drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
    it->displayInfo();
    
    drawTable({{L"SỬA THÔNG TIN"},
                {L"1. Họ tên."},
                {L"2. Số điện thoại."},
                {L"0. Quay lại."}});
    // drawTable(table);
    int choice;
    checkInput(L"Chọn thông tin cần sửa", choice);
    if(!choice) {
        return;
    }
    switch(choice) {
         case 1: {
            red(L"Nhập 0: Bỏ qua\n");
            drawTable({{L"Nhập họ và tên mới: ", L"                                  "}});
            Position pos = getXY();
            int x = pos.X;
            int y = pos.Y;
            wcin.ignore();
        inputName:
            gotoXY(26, y-2);
            wcout << L"                                  ";
            gotoXY(26, y-2);
            getline(wcin, newName);
            if(newName != L"0"){
                //check format tên
                wregex pattern(L"^[^\\n]([a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỈỊỌỎỐỒỔỖỘỚỜỞỠỢỤỦỨỪễệỉịọỏốồổỗộớờởỡợụủứừỬỮỰỲỴÝỶỸửữựỳỵỷỹ ]+)$");
                if (regex_match(newName, pattern)) {
                    Customer customerTmp = *it;
                    customerTmp.setName(newName);
                    system("cls");
                    drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
                    customerTmp.displayInfo();
                    wchar_t ct;
    
                    green(L"Xác nhận lưu thay đổi thông tin khách hàng? (y/n): ");
                    wcin >> ct;
                    ct = towlower(ct);
                    if(ct == 'y'){
                        it->setName(newName);
                        green(L"═════[Lưu thông tin thành công.]═════\n");  

                        CustomerList::saveToCSV("../DATA/customers.csv");
                    }else{
                        red(L"[Đã hủy thay đổi.]\n");
                    }

                }else{
                    gotoXY(x, y+1);
                    red(L"Tên không hợp lệ. Vui lòng nhập lại.\n");
                    newName.clear();
                    goto inputName;
                }
                
            }
            goto edit;
        }
        case 2: {
            red(L"Nhập 0: Bỏ qua\n");
            drawTable({{L"Nhập số điện thoại mới: ", L"                                  "}});
            Position pos = getXY();
            int x = pos.X;
            int y = pos.Y;
            wcin.ignore();
        inputPhone:
            gotoXY(30, y-2);
            wcout << L"                                  ";
            gotoXY(30, y-2);
            getline(wcin, newPhoneNumber);
            if(newPhoneNumber != L"0"){
                //check format số điện thoại
                wregex phonePattern(L"^(84|0)[0-9]{8,13}$");
                if (regex_match(newPhoneNumber, phonePattern)) {
                    
                    Customer *checkExist = CustomerList::findPhoneNumber(newPhoneNumber);
                    if(checkExist){
                        gotoXY(x, y+1);
                        red(L"Số điện thoại đã tồn tại. Vui lòng nhập lại.\n");
                        newPhoneNumber.clear();
                        goto inputPhone;
                    }

                    Customer customerTmp = *it;
                    customerTmp.setPhoneNumber(newPhoneNumber);
                    system("cls");
                    drawTable({{L"           THÔNG TIN KHÁCH HÀNG           "}});
                    customerTmp.displayInfo();
                    wchar_t ct;
    
                    green( L"Xác nhận lưu thay đổi thông tin khách hàng? (y/n): ");
                    wcin >> ct;
                    ct = towlower(ct);
                    if(ct == 'y'){
                        it->setPhoneNumber(newPhoneNumber);
                        green(L"═════[Lưu thông tin thành công.]═════\n");  

                        CustomerList::saveToCSV("../DATA/customers.csv");
                    }else{
                        red(L"[Đã hủy thay đổi.]\n");
                    }
                }else{
                    gotoXY(x, y+1);
                    red(L"Số điện thoại không hợp lệ. Vui lòng nhập lại.\n");
                    newPhoneNumber.clear();
                    goto inputPhone;
                }
            }
            goto edit;
        }
        default:
            red(L"Chọn không hợp lệ. Vui lòng chọn lại.\n");
            goto edit;
    }

}

void CustomerList::displayCustomers() const {
    vector<vector<wstring>> table;
    table.push_back({L"ID", L"Họ tên", L"Số điện thoại", L"Điểm" });
    for (const auto& customer : customers) {
        vector<wstring> row;
        row.push_back(to_wstring(customer.getCustomerID()));
        row.push_back(customer.getName());
        row.push_back(customer.getPhoneNumber());
        row.push_back(to_wstring(customer.getPoint()));
        table.push_back(row);
    }
    wcout << L"\n\n";
    drawTable(table);
}

void CustomerList::saveToCSV(string filename = "../DATA/customers.csv") const {   
    locale loc(locale(), new codecvt_utf8<wchar_t>);   // UTF-8

    wofstream file(filename);   // mở file để ghi
    if (file.is_open()) {
        file.imbue(loc);    // đọc được tiếng việt từ file
        file<<L"ID,Họ tên,Số điện thoại,Điểm\n";    // tiêu đề cột
        for (const auto& Customer : customers) {
            file << Customer.getCustomerID() << L","
                 << Customer.getName() << L",";
            file << Customer.getPhoneNumber() << L","
                 << Customer.getPoint() << L"," << endl;
        }
        file.close();
        green(L"Lưu danh sách khách hàng thành công\n");
    } else {
        wcerr << L"Không thể mở tập tin để lưu\n";
    }
}

void CustomerList::loadFromCSV(const string& filename) {
    customers.clear();
    wifstream file(filename);   // mở file để đọc
    locale loc(locale(), new codecvt_utf8<wchar_t>);   // UTF-8
    file.imbue(loc);    // đọc được tiếng việt từ file

    wstring line;   
    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        wstringstream ss(line);    // đọc từng dòng
        wstring id, name, phoneNumber, point;

        getline(ss, id, L',');  // đọc từng dữ liệu cách nhau bởi dấu phẩy
        getline(ss, name, L',');
        getline(ss, phoneNumber, L',');
        getline(ss, point);

        customers.push_back(Customer(stoi(id), name, phoneNumber, stoi(point)));
    }
    file.close();
}

Customer* CustomerList::findPhoneNumber(wstring phoneNumber) {
    auto it = find_if(customers.begin(), customers.end(), [phoneNumber](const Customer& customer) {
        return customer.getPhoneNumber() == phoneNumber;
    });
    if (it != customers.end()) {
        return &(*it);
    }
    return nullptr;
}

Customer *CustomerList::findCustomerID(int id)
{
    auto it = find_if(customers.begin(), customers.end(), [id](const Customer &customer) {
        return customer.getCustomerID() == id;
    });
    if (it != customers.end())
    {
        return &(*it);
    }
    return nullptr;

}

Customer *CustomerList::findCustomerName(wstring name)
{   
    // Hàm lambda để chuyển đổi chuỗi sang chữ thường
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };


    auto it = find_if(customers.begin(), customers.end(), [toLower, name](const Customer &customer) {
        return toLower(customer.getName()).find(toLower(name)) != std::wstring::npos;
    });
    if (it != customers.end())
    {
        return &(*it);
    }
    return nullptr;
}


Customer *CustomerList::findCustomerAll(wstring search, int &start)
{   
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };

    
    auto it = find_if(customers.begin() + start, customers.end(), [search, toLower](const Customer &customer) {
        return toLower(customer.getName()) == toLower(search) || customer.getPhoneNumber() == search || to_wstring(customer.getCustomerID()) == search;
    });
    if (it != customers.end())
    {   
        start = distance(customers.begin(), it); // Cập nhật vị trí của it vào start
        return &(*it);
    }
    return nullptr;
}

CustomerList::~CustomerList() {
}