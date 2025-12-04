/*----------------------------------------------------------------*/
// Name: Tạ Thị Nga
// Student ID: 20227026
// Class: Toán Tin 02 - K67
// Project: Chủ đề 2: Xây dựng "thư viện" phép toán với số nguyên lớn
// Date: 20/06/2024
/*-----------------------------------------------------------------*/


#include "SNL.cpp"

int main() {

    SNL soThu_1, soThu_2;
    bool docSo = false;

    while (true) {
        Menu();
        int luaChon;
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            // Case 1: Nhập 2 số nguyên lớn từ bàn phím
            {
                cout << "Nhap so nguyen lon thu nhat: ";
                cin >> soThu_1;
                cout << "Nhap so nguyen lon thu hai: ";
                cin >> soThu_2;
                docSo = true;
                case3(soThu_1, soThu_2);
                break;
            }
        case 2:
            // Case 2: Nhập từ file input.txt
            {
                ifstream inputFile("input.txt");
                if (inputFile.is_open()) {
                    inputFile >> soThu_1 >> soThu_2;
                    inputFile.close();
                    cout << "So nguyen lon thu nhat tu file: " << soThu_1 << '\n';
                    cout << "So nguyen lon thu hai tu file: " << soThu_2 << '\n';
                    docSo = true;
                } 
                else {
                    cout << "Khong the mo file input.txt\n";
                }
                case3(soThu_1, soThu_2);
                break;
            }

        case 4:
            // Case 4: Thoát
            {
                cout << "Thoat chuong trinh.\n";
                return 0;
            }
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    }
    return 0;
}

