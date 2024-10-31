#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H
#include "Customer.h"
#include <vector>
#include <string>
#include <algorithm> // std::remove_if
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>


class CustomerList {
private:
    std::vector<Customer> customers;

public:
    CustomerList();
    ~CustomerList();

    vector<Customer>& getCustomers();

    // Thêm một khách hàng vào danh sách
    void addCustomer( const wstring& name, const wstring& phoneNumber, int point);

    // Sửa thông tin một khách hàng trong danh sách
    void editCustomer(Customer updatedCustomer);

    // Xóa một khách hàng ra khỏi danh sách
    void deleteCustomer(int id);
    
    // Hiển thị tất cả các bộ phim trong danh sách
    void displayCustomers() const;

    // Lưu danh sách khác hàng vào tệp CSV
    void saveToCSV(string filename) const;

    // Đọc danh sách khách hàng từ tệp CSV
    void loadFromCSV(const std::string& filename);

};

#endif // CUSTOMERLIST_H