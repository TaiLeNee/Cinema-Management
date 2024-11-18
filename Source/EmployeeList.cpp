#include "../Header/EmployeeList.h"
#include "../Header/gotoXY.h"
#include "../Header/getXY.h"

int ListOfEmployee::nextID = 1;

void ListOfEmployee::addEmployee() {
    vector<vector<wstring>> table;
    wstring name, phoneNumber, userName, passWord;
    int age, level;

    wregex namePattern(L"^[^\\n]([a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỈỊỌỎỐỒỔỖỘỚỜỞỠỢỤỦỨỪễệỉịọỏốồổỗộớờởỡợụủứừỬỮỰỲỴÝỶỸửữựỳỵỷỹ ]+)$");
    wregex agePattern(L"^(1[89]|[2-5][0-9]|60)$");
    wregex phonePattern(L"^(84|0)[0-9]{8,13}$");

    table.push_back({L"              Nhập Thông Tin Của Nhân Viên Mới             "});
    table.push_back({L"Nhập tên của nhân viên:  "});
    table.push_back({L"Nhập tuổi của nhân viên: "});
    table.push_back({L"Nhập SĐT của nhân viên: "});
    table.push_back({L"Nhập cấp bậc của nhân viên (1. Admin, 2. Nhân viên):  "});
    drawTable(table);

    red(L"\nNhập 0: Quay lại\n");
    Position pos = getXY();
    int x = pos.X;
    int y = pos.Y;

    int newID = 1;
    if (!employee_list.empty()) {
        newID = max_element(employee_list.begin(), employee_list.end(), [](const Employee &a, const Employee &b) {
            return a.getId() < b.getId();
        })->getId() + 1;
    }

    Employee temp;
    inputName:
        gotoXY(28,3);
        wcout << L"                   ";
        gotoXY(28,3);
        
        getline(wcin, name);
        gotoXY(0,11);
        wcout << L"                                    ";
        if(name !=L"0"){
            if(regex_match(name, namePattern)){
                temp.setName(name);
            }
            else{
                gotoXY(0,11);
                red(L"[Tên không hợp lệ. Hãy nhập lại.]");
                name.clear();
                goto inputName;
            }
        }
        else {
            system("cls");
            return;
        }
    inputAge:
        gotoXY(28,5);
        wcout << L"                   ";
        gotoXY(28,5);
        wcin >> age;
        gotoXY(0,11);
        wcout << L"                                    ";
        wstring ageStr = to_wstring(age);
        if (age != 0){
            if (regex_match(ageStr, agePattern)){
                temp.setAge(age);
            }
            else{
                gotoXY(0,11);
                red(L"[Tuổi không hợp lệ. Hãy nhập lại.]");
                goto inputAge;
            }
        }
        else {
            wcin.ignore();
            goto inputName;
        }
    inputPhoneNumber:
        gotoXY(28,7);
        wcout << L"                   ";
        gotoXY(28,7);
        wcin.ignore();
        getline(wcin, phoneNumber);
        gotoXY(0,11);
        wcout << L"                                    ";
        if (phoneNumber!=L"0"){
            if (regex_match(phoneNumber, phonePattern)){
                temp.setPhoneNumber(phoneNumber);
            }
            else{
                gotoXY(0,11);
                red(L"[Số điện thoại không hợp lệ. Hãy nhập lại.]");
                goto inputPhoneNumber;
            }
        }
        else {
            goto inputAge;
        }
    inputLevel:
        gotoXY(56,9);
        wcout << L"  ";
        gotoXY(56,9);
        wcin >> level;
        gotoXY(0,11);
        wcout << L"    ";
        if(level == 2){
            userName = L"Nv_" + to_wstring(newID);
            passWord = L"123456";
        }
        else if (level == 1){
            userName = L"Admin_" + to_wstring(newID);
            passWord = L"123456";
        }
        else if (level == 0){
            goto inputPhoneNumber;
        }
        else{
            gotoXY(0,11);
            red(L"[Cấp bậc không hợp lệ. Hãy nhập lại.]");
            goto inputLevel;
        }
    system("cls");
    Employee newE(name, age, phoneNumber, userName, passWord, level);
    newE.setId(newID); 
    newE.displayInfo();
    wchar_t ct;
    green(L"Xác nhận thêm nhân viên mới ? (y/n): ");
    wcin >> ct;
    ct = tolower(ct);
    if (ct == 'y'){
        employee_list.push_back(newE);
        system("cls");
        green(L"[Đã thêm nhân viên mới]");
    }
    else{
        system("cls");
        red(L"[Đã hủy thêm nhân viên mới]");
    }
}

void ListOfEmployee::deleteEmployee(int id){
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e){
        return e.getId() == id;
    });
    if (it->getLevel() == 0) {
        wcout << L"\033[92m[Không thể xóa tài khoản OWNER]\033[0m" << endl;
        return;
    }
    wstring name = it->getName();
    if(it != employee_list.end()){
        system("cls");
        it->displayInfo();
        wchar_t ct;
        green(L"Xác nhân xóa nhân viên ? (y/n): ");
        wcin >> ct;
        ct = tolower(ct);
        system("cls");
        if (ct == 'y'){
            employee_list.erase(it);
            wcout << L"\033[92m[Đã xóa nhân viên "<< name <<L"] \033[0m" << endl;
        }
        else {
            red(L"[Đã hủy xóa nhân viên]\n");
        }
    }
}


void ListOfEmployee::showEmployeeInfo(int id) {
    wcout<< L"\033[0m";
    auto it = find_if(employee_list.begin(), employee_list.end(), [id]( Employee &e) {
        return e.getId() == id;
    });

    if (it == employee_list.end()) {
        wcout << L"\033[92m[Nhân viên không tồn tại] \033[0m" << endl;
        return;
    }

    vector<vector<wstring>> table;
    table.push_back({L"          Thông Tin Nhân Viên         "});
    table.push_back({L"ID: " + to_wstring(it->getId())});
    table.push_back({L"Tên: " + it->getName()});
    table.push_back({L"Tuổi: " + to_wstring(it->getAge())});
    table.push_back({L"Số Điện Thoại: " + it->getPhoneNumber()});
    table.push_back({L"Username: " + it->getUserName()});
    table.push_back({L"Password: " + it->getPassWord()});
    if (it->getLevel() == 1) {
        table.push_back({L"Cấp bậc: Admin"});
    } 
    else if (it->getLevel() == 2) {
        table.push_back({L"Cấp Bậc: Nhân viên"});
    }
    else if (it->getLevel() == 0) {
        table.push_back({L"Cấp Bậc: OWNER"});
    }
    
    drawTable(table);
}

void ListOfEmployee::showEmployeeList() const{
    vector<vector<wstring>> table1,table2;
    table1.push_back({L"Danh sách nhân viên"});
    drawTable(table1);
    table2.push_back({L"ID", L"Tên", L"Tuổi", L"Số Điện Thoại", L"Username", L"Password", L"Cấp Bậc"});
    for(const auto &e : employee_list){
        wstring level;
        if (e.getLevel() == 1) {
            level = L"Admin";
        }    
        else if (e.getLevel() == 2) {
            level = L"Nhân viên";
        }
        else if (e.getLevel() == 0) {
            level = L"Owner";
        }
        table2.push_back({to_wstring(e.getId()), 
        e.getName(), 
        to_wstring(e.getAge()), 
        e.getPhoneNumber(), 
        e.getUserName(), 
        e.getPassWord(), 
        level
        });
    }
    drawTable(table2);
}


void ListOfEmployee::editEmployeeInfo(int id) {
    int choice;
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e) {
        return e.getId() == id;
    });

    if (it == employee_list.end()) {
        wcout << L"\033[92m[Nhân viên không tồn tại] \033[0m" << endl;
        return;
    }
        vector<vector<wstring>> table;
        wstring name, phoneNumber, userName, passWord;
        int age, level;
        table.push_back({L"Hãy chọn thông tin bạn muốn sửa đổi"});
        table.push_back({L"1. Họ và tên"});
        table.push_back({L"2. Tuổi"});
        table.push_back({L"3. Số điện thoại"});
        table.push_back({L"4. Username"});
        table.push_back({L"5. Password"});
        table.push_back({L"6. Cấp bậc"});
        table.push_back({L"0. Thoát"});

    edit:
        system("cls");
        showEmployeeInfo(id);
        drawTable(table);
        checkInput(L"Nhập thông tin cần chỉnh sửa", choice);
        switch (choice){
            case 1: {
                red(L"Nhập 0: Bỏ qua\n");
                drawTable({{L"Nhập họ và tên mới: ", L"                                  "}});
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
                wcin.ignore();
            inputName:
                gotoXY(26, y-2);
                wcout << L"                           ";
                gotoXY(26, y-2);
                getline(wcin, name);
                if(name!=L"0"){
                    wregex pattern(L"^[^\\n]([a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỈỊỌỎỐỒỔỖỘỚỜỞỠỢỤỦỨỪễệỉịọỏốồổỗộớờởỡợụủứừỬỮỰỲỴÝỶỸửữựỳỵỷỹ ]+)$");
                    if (regex_match(name,pattern)){
                        Employee temp = *it;
                        temp.setName(name);
                        system("cls");
                        temp.displayInfo();
                        wchar_t ct;

                        green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                        wcin >> ct;
                        ct = tolower(ct);
                        if (ct == 'y'){
                            it->setName(name);
                            green(L"═════[Lưu thông tin thành công.]═════\n");  

                            saveEmployee("../Data/employee/csv");
                        }
                        else{
                            red(L"[Đã hủy thay đổi.]\n");
                        }
                    }
                    else{
                        gotoXY(x,y+2);
                        red(L"Tên không hợp lệ. Vui lòng nhập lại.\n");
                        name.clear();
                        goto inputName;
                    }
                }
                goto edit;
            }
            case 2: {
                red(L"Nhập 0: Bỏ qua\n");
                vector<vector<wstring>> table2;
                table2.push_back({L"Nhập tuổi mới: ", L"               "});
                drawTable(table2);
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
            inputAge:
                gotoXY(20, y-2);
                wcout << L"           ";
                gotoXY(20, y-2);
                wcin >> age;
                if(age!= 0){
                    wregex agePattern(L"^(1[89]|[2-5][0-9]|60)$");
                    wstring ageStr = to_wstring(age);
                    if (regex_match(ageStr,agePattern)){
                        Employee temp = *it;
                        temp.setAge(age);
                        system("cls");
                        temp.displayInfo();
                        wchar_t ct;

                        green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                        wcin >> ct;
                        ct = tolower(ct);
                        if (ct == 'y'){
                            it->setAge(age);
                            green(L"═════[Lưu thông tin thành công.]═════\n");  

                            saveEmployee("../Data/employee/csv");
                        }
                        else{
                            red(L"[Đã hủy thay đổi.]\n");
                        }
                    }
                    else{
                        gotoXY(x,y+2);
                        red(L"Tuổi không hợp lệ. Vui lòng nhập lại.\n");
                        name.clear();
                        goto inputAge;
                    }
                }
                goto edit;
            }
            case 3: {
                red(L"Nhập 0: Bỏ qua\n");
                vector<vector<wstring>> table3;
                table3.push_back({L"Nhập số điện thoại mới: ", L"               "});
                drawTable(table3);
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
                wcin.ignore();
            inputPhone:
                gotoXY(30, y-2);
                wcout << L"              ";
                gotoXY(30, y-2);
                getline(wcin, phoneNumber);
                if(phoneNumber!=L"0"){
                    wregex phonePattern(L"^(84|0)[0-9]{8,13}$");
                    if (regex_match(phoneNumber,phonePattern)){
                        Employee temp = *it;
                        temp.setPhoneNumber(phoneNumber);
                        system("cls");
                        temp.displayInfo();
                        wchar_t ct;

                        green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                        wcin >> ct;
                        ct = tolower(ct);
                        if (ct == 'y'){
                            it->setPhoneNumber(phoneNumber);
                            green(L"═════[Lưu thông tin thành công.]═════\n");  

                            saveEmployee("../Data/employee/csv");
                        }
                        else{
                            red(L"[Đã hủy thay đổi.]\n");
                        }
                    }
                    else{
                        gotoXY(x,y+2);
                        red(L"Số điện thoại không hợp lệ. Vui lòng nhập lại.\n");
                        name.clear();
                        goto inputPhone;
                    }
                }
                goto edit;
            }
            case 4: {
                red(L"Nhập 0: Bỏ qua\n");
                vector<vector<wstring>> table4;
                table4.push_back({L"Nhập tên đăng nhập mới: ", L"               "});
                drawTable(table4);
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
                wcin.ignore();
                gotoXY(28, y-2);
                wcout << L"             ";
                gotoXY(28, y-2);
                getline(wcin, userName);
                if(userName!=L"0"){
                    Employee temp = *it;
                    temp.setUserName(userName);
                    system("cls");
                    temp.displayInfo();
                    wchar_t ct;

                    green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                    wcin >> ct;
                    ct = tolower(ct);
                    if (ct == 'y'){
                        it->setUserName(userName);
                        green(L"═════[Lưu thông tin thành công.]═════\n");  

                        saveEmployee("../Data/employee/csv");
                    }
                    else{
                        red(L"[Đã hủy thay đổi.]\n");
                    }
                }
                goto edit;
            }
            case 5: {
                red(L"Nhập 0: Bỏ qua\n");
                vector<vector<wstring>> table5;
                table5.push_back({L"Nhập mật khẩu mới: ", L"               "});
                drawTable(table5);
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
                wcin.ignore();
                gotoXY(23, y-2);
                wcout << L"            ";
                gotoXY(23, y-2);
                getline(wcin, passWord);
                if(passWord!=L"0"){
                    Employee temp = *it;
                    temp.setPassWord(passWord);
                    system("cls");
                    temp.displayInfo();
                    wchar_t ct;

                    green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                    wcin >> ct;
                    ct = tolower(ct);
                    if (ct == 'y'){
                        it->setPassWord(passWord);
                        green(L"═════[Lưu thông tin thành công.]═════\n");  

                        saveEmployee("../Data/employee/csv");
                    }
                    else{
                        red(L"[Đã hủy thay đổi.]\n");
                    }
                }
                goto edit;
            }
            case 6: {
                red(L"Nhập 0: Bỏ qua\n");
                red(L"1. Admin, 2.Nhân Viên\n");
                vector<vector<wstring>> table6;
                table6.push_back({L"Nhập cấp bậc mới: ", L"               "});
                drawTable(table6);
                Position pos = getXY();
                int x = pos.X;
                int y = pos.Y;
            inputLevel:
                gotoXY(28, y-2);
                wcout << L"             ";
                gotoXY(28, y-2);
                wcin >> level;
                if(level != 0){
                    Employee temp = *it;
                    if(level == 2){
                        userName = L"Nv" + to_wstring(it->getId());
                        passWord = L"123456";
                    }
                    else if (level == 1){
                        userName = L"Admin_" + to_wstring(it->getId());
                        passWord = L"123456";
                    }
                    else{
                        red(L"[Cấp bậc không hợp lệ. Hãy nhập lại.\n]");
                        goto inputLevel;
                    }
                    temp.setLevel(level);
                    temp.setUserName(userName);
                    temp.setPassWord(passWord);
                    system("cls");
                    temp.displayInfo();
                    wchar_t ct;

                    green(L"Xác nhận thay đổi thông tin nhân viên ? (y/n): ");
                    wcin >> ct;
                    ct = tolower(ct);
                    if (ct == 'y'){
                        it->setLevel(level);
                        it->setUserName(userName);
                        it->setPassWord(passWord);
                        green(L"═════[Lưu thông tin thành công.]═════\n");
                        saveEmployee("../Data/employee/csv");
                    }
                    else{
                        red(L"[Đã hủy thay đổi.]\n");
                    }
                }
                goto edit;
            }
            case 0: {
                return;
            }  
            default:{
                wcout << L"\033[92m[Lựa chọn không hợp lệ] \033[0m" << endl;
                break;
            }
        }
}

void ListOfEmployee::findEmployee(const wstring &name){

     auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };


    int id;
    vector<vector<wstring>> table1,table2;
    green(L"\nCác nhân viên với tên " + name + L" là: \n");
    table1.push_back({L"ID", L"Tên", L"Tuổi", L"Số Điện Thoại", L"Username", L"Password", L"Cấp Bậc"});
    for(const auto &e : employee_list){
        if(toLower(e.getName()).find(toLower(name)) != wstring::npos){
            wstring level;
            if (e.getLevel() == 1) {
                level = L"Admin";
            }    
            else if (e.getLevel() == 2) {
                level = L"Nhân viên";
            }
            else if (e.getLevel() == 0) {
                level = L"Owner";
            }
            table1.push_back({to_wstring(e.getId()), 
            e.getName(), 
            to_wstring(e.getAge()), 
            e.getPhoneNumber(), 
            e.getUserName(), 
            e.getPassWord(), 
            level
            });
        }
    }
    drawTable(table1);
    
}

Employee* ListOfEmployee::findEmployeeByID(int id){
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e){
        return e.getId() == id;
    });
    if(it != employee_list.end()){
        return &(*it);
    }
    return nullptr;
}

Employee* ListOfEmployee::findEmployeeByName(const wstring &name){
    // Hàm lambda để chuyển đổi chuỗi sang chữ thường
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };


    auto it = find_if(employee_list.begin(), employee_list.end(), [toLower, name](Employee &e){
        return toLower(e.getName()).find(toLower(name)) != std::wstring::npos;
    });
    if(it != employee_list.end()){
        return &(*it);
    }
    return nullptr;
}

void ListOfEmployee::interactWithEmployee(int id){
    int choice;
    do{
        system("cls");
        showEmployeeInfo(id);
        vector<vector<wstring>> table;
        table.push_back({L"1. Chỉnh sửa thông tin nhân viên"});
        table.push_back({L"2. Xóa nhân viên"});
        table.push_back({L"0. Thoát"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        switch (choice){
            case 1:
                system("cls");
                editEmployeeInfo(id);
                break;
            case 2:
                system("cls");
                deleteEmployee(id);
                break;
            case 0:
                system("cls");
                break;
            default:
                wcout << L"\033[92m[Lựa chọn không hợp lệ] \033[0m" << endl;
                break;
        }
    }while(choice != 0 && choice !=2);
}

void ListOfEmployee::saveEmployee(const string& filename) const {
    // Sử dụng wofstream để hỗ trợ ghi tiếng Việt
    wofstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // Thiết lập ghi UTF-8

    if (file.is_open()) {
        // Ghi tiêu đề cột
        file << L"ID,Tên,Tuổi,Số Điện Thoại,Username,Password,Level" << endl;

        // Ghi thông tin từng nhân viên
        for (const auto &e : employee_list) {
            file << e.getId() << L","
                 << e.getName() << L","
                 << e.getAge() << L","
                 << e.getPhoneNumber() << L","
                 << e.getUserName() << L","
                 << e.getPassWord() << L","
                 << e.getLevel() << endl;
        }
    } else {
        wcout << L"Không thể mở file để lưu trữ thông tin nhân viên" << endl;
    }
}

// Hàm tải danh sách nhân viên từ file CSV
void ListOfEmployee::loadEmployees(const string& filename) {
    // Sử dụng wifstream để hỗ trợ đọc tiếng Việt
    wifstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // Thiết lập đọc UTF-8

    if (!file.is_open()) {
        wcerr << L"Không thể mở file: " << filename.c_str() << endl;
        return; 
    }

    wstring line;
    getline(file, line); 

    while (getline(file, line)) {
        wstringstream ss(line);
        wstring token;

        int id, age, level;
        wstring name, phoneNumber, userName, passWord;

        getline(ss, token, L',');
        id = stoi(token);

        getline(ss, name, L',');

        getline(ss, token, L',');
        age = stoi(token);

        getline(ss, phoneNumber, L',');

        getline(ss, userName, L',');

        getline(ss, passWord, L',');

        getline(ss, token, L',');
        level = stoi(token);

        Employee e(name, age, phoneNumber, userName, passWord, level);
        e.setId(id);
        employee_list.push_back(e);
    }
    file.close();
}

Employee *ListOfEmployee::signIn(const wstring &userName, const wstring &passWord) {
    auto it = find_if(employee_list.begin(), employee_list.end(), [userName, passWord](Employee &e) {
        return e.getUserName() == userName && e.getPassWord() == passWord;
    });

    if (it != employee_list.end()) {
        return &(*it);
    }

    return nullptr;
}

int ListOfEmployee::createID(){
    return nextID++;
}

vector<Employee> &ListOfEmployee::getEmployees()
{
    return employee_list;
}
