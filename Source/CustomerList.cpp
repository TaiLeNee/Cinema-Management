#include "../Header/Customer.h"
#include "../Header/CustomerList.h"

using namespace std;

CustomerList::CustomerList() {
    loadFromCSV("../DATA/customers.csv");
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

void CustomerList::editCustomer(int id, Customer updatedCustomer) {
    customer:
    drawTable({
        {L"   THAY ĐỔI THÔNG TIN KHÁCH HÀNG    "},
        {L"1. Họ tên.                          "},
        {L"2. Số điện thoại.                   "},
    });
    int choice;
    wstring newName;
    wstring newPhoneNumber;
    wcin >> choice;
    switch(choice) {
        case 1:
            wcout << endl << L"Họ và tên mới: ";
            wcin.ignore();
            getline(wcin,newName);
            updatedCustomer.setName(newName);
            break;
        case 2:
            wcout << endl << L"Số điện thoại mới: ";
            wcin.ignore();
            getline(wcin,newPhoneNumber);
            updatedCustomer.setPhoneNumber(newPhoneNumber);
            break;
        default:
            wcout << L"Lựa chọn không hợp lệ!! Hãy chọn lại\n";
            goto customer;
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
    }
    file.close();
}

CustomerList::~CustomerList() {
}