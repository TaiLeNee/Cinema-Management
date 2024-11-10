#include "../Header/Menu.h"
#include "../Header/checkInput.h"
#include "../Header/globals.h"

void countdown(int duration) {

    for (int i = 1; i <= duration; i++) {
       green(L"\rĐang xác nhận: " + to_wstring(i) + L" giây");
        wcout<<flush;
        Sleep(1000);
    }
    Sleep(1000);
}


void SellTicketInWeek(MovieList &movieList, RoomList &roomList) {   
    BookedList bookedList;
    bookedList.loadChairbookedFromCSV("../DATA/payments.csv");

    wstring GREEN = L"\033[92m";
    wstring YELLOW = L"\033[93m";
    
    wstring dateBooking, movieNameBooking, showtimeBooking, chairBooking,ticketBooking, roomBooking, totalMoneyBooking, paymentMethodBooking, employeeBooking, customerBooking;

    vector<vector<wstring>> table;
    vector<wstring>date;
    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);

    table.push_back({L"Ngày chiếu phim"}); 
    table.push_back({L"[1]. Hôm nay: " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    
    date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));

    now += 24 * 60 * 60;
    ltm = localtime(&now);
    table.push_back({L"[2]. Ngày mai: " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));
    
    //Các ngày trong tuần 1 tuần

    for(int i = 2; i < 7; i++){
        now += 24 * 60 * 60;
        tm *ltm = localtime(&now);
        table.push_back({ L"["+to_wstring(i+1)+L"]" + L". " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
        date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));

    }

Date:
    system("cls");
    drawTable(table);
    wcout<<L"\033[91mNhập 0: Quay lại\n";

    // wcout<<L"\033[92m════════[Chọn ngày]==> ";
    int choiceDate ;
    checkInput(L"Chọn ngày", choiceDate);;

    if(choiceDate == 0){
        system("cls");
        return;
    }
    else if(choiceDate < 0 || choiceDate > 7){
        red(L"Chọn sai. Vui lòng chọn lại.\n");
        goto Date;
    }
    
    vector<vector<wstring>> tableMovie;
    tableMovie.push_back({L"Chọn", L"ID", L"Danh sách phim trong ngày: " + date[choiceDate-1]});


    for(auto &movie: movieList.getMovies()){
        for(auto &showtime: movie->getShowtimes()){
            if(showtime.getStartTime().getDate() == date[choiceDate-1]){

                tableMovie.push_back({ L"["+to_wstring(showtime.movieID) + L"]" , to_wstring(showtime.showtimeID) , movie->getName()});

                showtime.loadChairbooked(bookedList);

                break;
            }
        }
    }

    /// Hiện thị danh sách phim trong ngày
MovieInDay:
    dateBooking = date[choiceDate-1];

    drawTable(tableMovie);
    wcout<<L"\033[91mNhập 0: Quay lại\n";
    // wcout<<L"\033[92m════════[Chọn phim]==> ";
    int choiceMovie;
    checkInput(L"Chọn phim", choiceMovie);
    if(!choiceMovie)
        goto Date;
    
    if(find_if(tableMovie.begin(), tableMovie.end(), [choiceMovie](vector<wstring> movie){
        return movie[0] == L"["+to_wstring(choiceMovie)+L"]";
    }) == tableMovie.end()){
        red(L"Chọn sai. Vui lòng chọn lại.\n");
        goto MovieInDay;
    }
    

ShowtimeInDay:
    //hiển thị Showtimes có trong ngày của phim đó
    system("cls");
    auto it = find_if(movieList.getMovies().begin(), movieList.getMovies().end(), [choiceMovie](Movie* movie){
            return movie->getId() == choiceMovie;
        });

    Movie* movie = (it != movieList.getMovies().end()) ? *it : NULL;
    if(!movie){
        red(L"[Phim không tồn tại. Vui lòng chọn lại.]\n");
        goto MovieInDay;
    }
    drawTable({{L"     THÔNG TIN PHIM ĐÃ CHỌN   "}});

    movie->displayInfo();

    movie->displayShowtimeInDay(date[choiceDate-1]);
    
    movieNameBooking = movie->getName();

    //Lấy showtimeID
    int showtimeID = -1;
    int choiceShowtime;
    red(L"Nhập 0:quay lại\n");
    checkInput(L"Chọn suất chiếu", choiceShowtime);
    if(choiceShowtime == 0){
        system("cls");
        goto MovieInDay;
    }

    bool checkShowtime = false;
    for(auto& showtime: movie->getShowtimes()){
        if(showtime.getStartTime().getDate() == date[choiceDate-1] && showtime.showtimeID == choiceShowtime){
            showtimeID = showtime.showtimeID;
            checkShowtime = true;
            break;
        }
    }



    if(showtimeID == -1){
        system("cls");
        red(L"[Chọn sai. Vui lòng chọn lại.]\n");
        goto ShowtimeInDay;
    }

    if(!checkShowtime){
        system("cls");
        red(L"[Suất chiếu không tồn tại. Vui lòng chọn lại.]\n");
        goto ShowtimeInDay;
    }

    
    system("cls");
    
    auto &showtimes = movie->showtimes;
   

    // Chọn loại vé
    TicketList ticketList;

choiceTicket:
    green(L"==================================\n");
    drawTable({{L"       BẢNG GIÁ VÉ        "}});
    ticketList.displayTickets();
    red(L"Nhập 0: quay lại\n");
    int ticketID;
    checkInput(L"Chọn loại vé", ticketID);
    if(ticketID == 0){
        system("cls");
        goto ShowtimeInDay;
    }

    if (ticketID < 0 || ticketID > ticketList.getTickets().size()) {
        system("cls");
        red(L"Chọn sai. Vui lòng chọn lại.\n");
        goto choiceTicket;
    }


    int numChairs;
    checkInput(L"═══Số lượng ghế═══", numChairs);
    if(numChairs <= 0){
        system("cls");
        red(L"Số lượng ghế không hợp lệ. Vui lòng nhập lại.\n");
        goto choiceTicket;
    }

    system("cls");
    int totalMoney = 0;
    //Hiển thị thông tin loại vé và số lượng ghế
    for(auto& ticket: ticketList.getTickets()){
        if(ticket.getTicketID() == ticketID){
            //lấy loại vé
            ticketBooking = ticket.getTypeTicket();
            //Tính tổng tiền vé
            totalMoney = ticket.getPrice() * numChairs;

            drawTable({{L"     THÔNG TIN VÉ ĐÃ CHỌN   "}});
            drawTable({{L"Loại vé", L"Giá vé", L"Số lượng ghế", L"Tổng tiền vé"},
                        {ticket.getTypeTicket(), to_wstring(ticket.getPrice()), to_wstring(numChairs), to_wstring(totalMoney) }});
            break;
        }
    }

    // wcin.ignore();
    wcout<<GREEN<<L"═══[ Nhấn Enter để chọn ghế hoặc 0 để quay lại ... ]==> ";
    wcin.get();
    if(wcin.get() == '0'){
        system("cls");
        goto choiceTicket;
    }



    //Chọn ghế
choiceChair:
    Showtime *showtimeCurrent;

    for (auto &showtime : showtimes) {
        if (showtime.showtimeID == showtimeID) {
            showtime.displayChairs(ticketID);
            showtimeCurrent = &showtime;
            break;
        }
    }

    showtimeBooking = showtimeCurrent->getStartTime().getFulltime();

    red(L"Nhập 0: quay lại\n");
    wcout << GREEN << L"══════[ Chọn ghế ]══════\n";

    vector<wstring> chairNames;
    for (int i = 0; i < numChairs; ++i) {
        wstring chairName;
        wcout<<GREEN<<L"══╬═══[Nhập tên ghế thứ " << i + 1 << L"]==> ";
        wcin >> chairName;
        if(chairName == L"0"){
            system("cls");
            goto choiceTicket;
        }
        

        wregex pattern(L"^[A-Z]\\d{1,2}$"); // Định dạng tên ghế
        if (!regex_match(chairName, pattern)) {
            red(L"Tên ghế không hợp lệ. Vui lòng nhập lại.\n");
            --i;
            continue;
        }

        if(find(chairNames.begin(), chairNames.end(), chairName) != chairNames.end()){
            red(L"Ghế đã được chọn trước đó. Vui lòng chọn ghế khác.\n");
            --i;
            continue;
        }

        if(showtimeCurrent->checkChairExist(showtimeID, chairName)){
            red(L"Ghế không tồn tại hoặc đã được đặt. Vui lòng chọn ghế khác.\n");
            --i;
            continue;
        }
        
        chairNames.push_back(chairName);
        chairBooking += chairName + L", ";
    }
    
    // Đặt vé
    auto roomIt = find_if(roomList.getRooms().begin(), roomList.getRooms().end(), 
        [&](Room& room) {
            return any_of(room.getShowtimes().begin(), room.getShowtimes().end(), 
                [&](const Showtime& showtime) {
                    return showtime.showtimeID == showtimeCurrent->showtimeID;
                });
        });

    if (roomIt != roomList.getRooms().end()) {
        roomBooking = roomIt->getName();
    }


    showtimeCurrent->bookTickets(ticketID, chairNames, 2);
    showtimeCurrent->displayChairs(ticketID);   

    employeeBooking = loggedin_global->getName();
    
    //Xử lý yes no
    wcout<<GREEN<<L"══════[Xác nhận thanh toán]══════\n";   
    drawTable({{L"        THÔNG TIN VÉ         "}});
    drawTable({
        {L"Nhân viên: ", employeeBooking},
        {L"",L""},
        {L"Tên phim: ", movieNameBooking},
        {L"Ngày chiếu: ", dateBooking},
        {L"Suất chiếu: ", showtimeBooking},
        {L"Phòng chiếu: ", roomBooking},
        {L"Loại vé: ", ticketBooking},
        {L"Số lượng ghế: ", to_wstring(numChairs)},
        {L"Ghế: ", chairBooking},
        {L"Tổng tiền: ", to_wstring(totalMoney)},
    });


    wcout<<GREEN<<L"══════[Nhập Yes hoặc No để tiếp tục ... Y/N (y/n)]==> ";
    wchar_t c;
    wcin>>c;
    c = towlower(c);
    if(c != 'y'){
        system("cls");
        showtimeCurrent->bookTickets(ticketID, chairNames, 0);
        red(L"══════[Đặt hủy đặt vé]══════\n");
        Sleep(1000);
        return;
    }


    //lấy thời gian hiện tại để lưu vào vé
    time_t now_date = time(0);
    tm *ltm_now = localtime(&now_date);
    wstring datetime = to_wstring(ltm_now->tm_hour) + L":" + to_wstring(ltm_now->tm_min) + L":" + to_wstring(ltm_now->tm_sec) + L" " + to_wstring(ltm_now->tm_mday) + L"/" + to_wstring(1 + ltm_now->tm_mon) + L"/" + to_wstring(1900 + ltm_now->tm_year)  ;

    
    

    showtimeCurrent->bookTickets(ticketID, chairNames, 1);
    // Lưu thông tin vé vào file
    Booked booked(ticketID, showtimeID, employeeIDLogin , datetime, to_wstring(totalMoney), chairNames);

    //Thanh toán
    wcout<<GREEN<<L"══════[Thanh toán]══════\n";

    Position posPayment;
    posPayment = getXY();
    int xPayment = posPayment.X;
    int yPayment = posPayment.Y;

choicePayment:
    gotoXY(xPayment, yPayment);

    drawTable({
        {L"PHƯƠNG THỨC THANH TOÁN"},
        {L"[1]. Tiền mặt"},
        {L"[2]. Chuyển khoản"},
        // {L"[3]. Thẻ"},
        {L"[0]. Hủy thanh toán"}
    });

    Pay* payment;
    int choicePayment;
    checkInput(L"Chọn phương thức thanh toán", choicePayment);
    if(choicePayment == 1){
        paymentMethodBooking = L"Tiền mặt";
        
        payment = new Cash();
        payment->setPaymentAmount(totalMoney);

        payment->setPaymentStatus(2);

        wstring confirmPay;
        green(L"══[Xác nhận đã nhận tiền (Y/N) ...]==> ");
        wcin>>confirmPay;
        if(confirmPay == L"Y" || confirmPay == L"y"){
            payment->setPaymentStatus(1);
            payment->checkPaymentStatus();

        }
        else{
            payment->setPaymentStatus(0);
        }

        
    }
    else if(choicePayment == 2){
        paymentMethodBooking = L"Chuyển khoản";
        payment = new Banking();
        payment->setPaymentAmount(totalMoney);
        payment->setPaymentStatus(2);

        wstring confirmPay;
        green(L"══[Xác nhận đã chuyển khoản (Y/N) ...]==> ");
        wcin>>confirmPay;
        if(confirmPay == L"Y" || confirmPay == L"y"){
            payment->setPaymentStatus(1);
            countdown(3);
            payment->checkPaymentStatus();
        }
        else{
            payment->setPaymentStatus(0);
        }
    }
    
    else if(choicePayment == 0){
        system("cls");
        showtimeCurrent->bookTickets(ticketID, chairNames, 0);
        red(L"══════[Thanh toán hủy]══════\n");
        Sleep(1000);
        return;
    }
    else{
        system("cls");
        red(L"Chọn sai. Vui lòng chọn lại.\n");
        goto choicePayment;
    }

    bookedList.addBooked(booked);
    booked.saveChairbooked();

    paymentMethodBooking = payment->processPayment();

    // showtimeCurrent->displayChairs(ticketID);
    green(L"══════[Đặt vé thành công]══════\n");
    wcout<<GREEN<<L"══════[Nhấn Enter để tiếp tục ... ]";
    wcin.ignore();
    wcin.get();
}

