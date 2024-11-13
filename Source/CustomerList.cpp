#include "../Header/Customer.h"
#include "../Header/CustomerList.h"

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
    customers.erase(remove_if(customers.begin(), customers.end(), [id](const Customer& customer) {
        return customer.getCustomerID() == id;
    }), customers.end());
}

void CustomerList::editCustomer(int id) {
    auto it = find_if(customers.begin(), customers.end(), [id](const Customer& customer) {
        return customer.getCustomerID() == id;
    });
   vector<vector<wstring>> table;
    wstring newName,newPhoneNumber;
    int newPoint;
    table.push_back({L"SỬA THÔNG TIN"});
    table.push_back({L"1. Họ tên."});
    table.push_back({L"2. Số điện thoại."});
    table.push_back({L"0. Quay lại."});

    edit:
    drawTable(table);
    int choice;
    checkInput(L"Chọn thông tin cần sửa", choice);
    if(!choice) {
        return;
    }
    switch(choice) {
         case 1: {
            wcout << L"Nhập họ và tên mới: ";
            wcin.ignore();
            getline(wcin, newName);
            wregex pattern(L"^[\\p{L}\\s]+$");
            if (regex_match(newName, pattern)) {
               it->setName(newName);
            } else {
                red(L"Tên không hợp lệ. Vui lòng nhập lại.\n");
            }
            goto edit;
        }
        case 2: {
            wcout << L"Nhập số điện thoại mới: ";
            wcin.ignore();
            getline(wcin, newPhoneNumber);
            wregex phonePattern(L"^(84|0)[0-9]{8,13}$");
            if (regex_match(newPhoneNumber, phonePattern)) {
                it->setPhoneNumber(newPhoneNumber);
            } else {
                red(L"Số điện thoại không hợp lệ. Vui lòng nhập lại.\n");
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

CustomerList::~CustomerList() {
}