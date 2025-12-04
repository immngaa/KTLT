/*----------------------------------------------------------------*/
// Name: Tạ Thị Nga
// Student ID: 20227026
// Class: Toán Tin 02 - K67
// Project: Chủ đề 2: Xây dựng "thư viện" phép toán với số nguyên lớn
// Date: 20/06/2024
/*-----------------------------------------------------------------*/

#include "SNL.h"

const int BASE = 10;

/*------------------------------- Xây dựng các hàm -------------------------------- */ 
SNL::SNL() {
    //SNL được khởi tạo với giá trị 0
    dauCuaSo = Duong;
    chuSoNguyenLon = 1;
    soNguyenLon.push_back('0');
}

SNL::SNL(int num) {
    //SNL được khởi tạo với giá trị num
    dauCuaSo = (num < 0) ? Am : Duong;
    num = abs(num);

    if (num == 0) {
        soNguyenLon.push_back('0');
    } 
    else {
        while (num > 0) {
            soNguyenLon.push_back('0' + num % BASE);
            num /= BASE;
        }
    }
    chuSoNguyenLon = soNguyenLon.size();
}

SNL::SNL(const string & s) {
    /* 
    - Điều kiện: s chỉ bao gồm các chữ số, có thể có dấu + hoặc - ở đầu. 
    - SNL được khởi tạo với giá trị số nguyên biểu diễn bởi s. 
    Nếu s không phải là một SNL đúng định dạng (Ví dụ, chứa các ký tự không phải chữ số), 
    thì một thông báo lỗi sẽ được in ra và hàm abort sẽ được gọi.
    */
    int limit = 0;

    if (s.empty()) {
        soNguyenLon.push_back('0');
        chuSoNguyenLon = 1;
        dauCuaSo = Duong;
        return;
    }

    if (s[0] == '-') {
        dauCuaSo = Am;
        limit = 1;
    } 
    else {
        dauCuaSo = Duong;
        if (s[0] == '+') {
            limit = 1;
        }
    }

    for (int k = s.length() - 1; k >= limit; k--) {
        if (!isdigit(s[k])) {
            cerr << "So khong hop le, hay nhap lai. " << endl;
            abort();
        }
        soNguyenLon.push_back(s[k]);
    }

    chuSoNguyenLon = soNguyenLon.size();
    chuanHoa();
}


bool SNL::coLaSoAm() const {
    // kiểm tra số âm
    return dauCuaSo == Am;
}

bool SNL::coLaSoDuong() const {
    // kiểm tra số dương
    return dauCuaSo == Duong;
}

int SNL::soChuSo() const {
    // trả về số chữ số của soNguyenLon
    return chuSoNguyenLon;
}

int SNL::layChuSo(int k) const {
    // lấy chữ số tại vị trí k
    if (0 <= k && k < soChuSo())
        return soNguyenLon[k] - '0';
    return 0;
}

void SNL::themChuSo(int giaTri) {
    // thêm chữ số có giaTri vào
    int len = soNguyenLon.size();
    if (chuSoNguyenLon >= len)
        soNguyenLon.resize(len * 2);

    soNguyenLon[chuSoNguyenLon] = char('0' + giaTri);
    chuSoNguyenLon++;
}

void SNL::thayDoiChuSo(int k, int giaTri) {
    // thay đổi chữ số tại vị trí k thành số có giaTri
    if (0 <= k && k < soChuSo())
        soNguyenLon[k] = char('0' + giaTri);
    else
        cerr << "Khong the thay doi chu so." << k << " " << chuSoNguyenLon << endl;
}

void SNL::chuanHoa() {
    // chuẩn hóa các soNguyenLon có số 0 ở đầu
    while (chuSoNguyenLon > 1 && soNguyenLon[chuSoNguyenLon - 1] == '0') {
        chuSoNguyenLon--;
    }
    if (chuSoNguyenLon == 1 && soNguyenLon[0] == '0') {
        dauCuaSo = Duong;
    }
}


string SNL::ToString() const {
    // Chuyển thành chuỗi
    string s = (coLaSoAm()) ? "-" : "";
    for (int k = chuSoNguyenLon - 1; k >= 0; k--)
        s += soNguyenLon[k];
    return s;
}

int SNL::ToInt() const {
    //Chuyển thành số nguyên
    int ketQua = 0;
    for (int k = soChuSo() - 1; k >= 0; k--) {
        ketQua = ketQua * 10 + layChuSo(k);
    }
    if (coLaSoAm())
        ketQua *= -1;
    return ketQua;
}

double SNL::ToDouble() const {
    //Chuyển thành số thực
    double ketQua = 0.0;
    for (int k = soChuSo() - 1; k >= 0; k--) {
        ketQua = ketQua * 10 + layChuSo(k);
    }
    if (coLaSoAm())
        ketQua *= -1;
    return ketQua;
}

bool SNL::Bang(const SNL & b) const {
    // So sánh bằng
    if (soChuSo() != b.soChuSo() || coLaSoAm() != b.coLaSoAm())
        return false;
    for (int k = 0; k < soChuSo(); k++) {
        if (layChuSo(k) != b.layChuSo(k))
            return false;
    }
    return true;
}

bool SNL::nhoHon(const SNL & b) const {
    // So sánh nhỏ hơn
    if (coLaSoAm() != b.coLaSoAm())
        return coLaSoAm();
    if (soChuSo() != b.soChuSo()) {
        return (soChuSo() < b.soChuSo() && coLaSoDuong()) || (soChuSo() > b.soChuSo() && coLaSoAm());
    }
    for (int k = soChuSo() - 1; k >= 0; k--) {
        if (layChuSo(k) < b.layChuSo(k))
            return coLaSoDuong();
        if (layChuSo(k) > b.layChuSo(k))
            return coLaSoAm();
    }
    return false;
}

/*==================== Các phép +=, -=, *=, /= gán vào số trước =========================*/
const SNL & SNL::operator +=(const SNL & b) {
    // Hàm trả về giá trị SNL + b  sau khi cộng
    int tong;
    int nho = 0; //biến nhớ
    int len = max(soChuSo(), b.soChuSo()); //độ dài

    if (coLaSoDuong() != b.coLaSoDuong()) {
        *this -= (-1 * b);
        return *this;
    }

    for (int k = 0; k < len; k++) {
        tong = layChuSo(k) + b.layChuSo(k) + nho;
        nho = tong / BASE;
        tong %= BASE;
        if (k < chuSoNguyenLon) {
            thayDoiChuSo(k, tong);
        } else {
            themChuSo(tong);
        }
    }

    if (nho != 0) {
        themChuSo(nho);
    }

    return *this;
}

const SNL & SNL::operator -=(const SNL & b) {
    int hieu;
    int nho = 0; //biến nhớ
    int len = soChuSo(); // độ dài

    if (this == &b) {
        *this = SNL(0);
        return *this;
    }

    if (coLaSoAm() != b.coLaSoAm()) {
        *this += (-1 * b);
        return *this;
    }

    if ((coLaSoDuong() && *this < b) || (coLaSoAm() && *this > b)) {
        *this = b - *this;
        dauCuaSo = coLaSoDuong() ? Am : Duong;
        return *this;
    }

    for (int k = 0; k < len; k++) {
        hieu = layChuSo(k) - b.layChuSo(k) - nho;
        nho = 0;
        if (hieu < 0) {
            hieu += BASE;
            nho = 1;
        }
        thayDoiChuSo(k, hieu);
    }

    chuanHoa();

    return *this;
}

const SNL & SNL::operator *=(const SNL & b) {
    SNL tich;
    tich.chuSoNguyenLon = soChuSo() + b.soChuSo();
    tich.soNguyenLon.assign(tich.chuSoNguyenLon, '0');

    for (int i = 0; i < soChuSo(); i++) {
        int nho = 0; // biến nhớ
        for (int j = 0; j < b.soChuSo(); j++) {
            int tmp = (tich.layChuSo(i + j) + layChuSo(i) * b.layChuSo(j) + nho);
            nho = tmp / BASE;
            tich.thayDoiChuSo(i + j, tmp % BASE);
        }
        if (nho != 0) {
            tich.thayDoiChuSo(i + b.soChuSo(), nho);
        }
    }

    tich.chuanHoa();
    tich.dauCuaSo = (coLaSoAm() == b.coLaSoAm()) ? Duong : Am;
    *this = tich;
    return *this;
}

const SNL & SNL::operator *=(int num) {
    if (num == 0) {
        *this = SNL(0);
        return *this;
    }
    if (num == 1) {
        return *this;
    }

    SNL nhanTu(num);
    *this *= nhanTu;
    return *this;
}

SNL du; // số dư
const SNL & SNL::operator /=(const SNL & b) {
    if (b == SNL(0)) {
        cerr << "Khong the chia duoc cho 0" << endl;
        *this = SNL(0); // Đặt giá trị thành 0
        return *this;
    }

    // Nếu b là số âm thì dùng biết tmp = abs(b)
    SNL tmp = b;
    if (tmp.coLaSoAm()) {
        tmp.dauCuaSo = Duong;
    }

    SNL thuong; //Thương
    thuong.chuSoNguyenLon = soChuSo();
    thuong.soNguyenLon.assign(thuong.chuSoNguyenLon, '0');

    du = SNL(0);
    for (int i = soChuSo() - 1; i >= 0; i--) {
        du *= BASE;
        du.thayDoiChuSo(0, layChuSo(i));
        int x = 0;
        int low = 0;
        int high = BASE - 1;
        // Dùng tìm kiếm nhị phân
        while (low <= high) {
            int mid = (low + high) / 2;
            SNL temp = tmp * mid;
            if (temp <= du) {
                x = mid;
                low = mid + 1;
            } 
            else 
                high = mid - 1;
        }
        thuong.thayDoiChuSo(i, x);
        du -= tmp * x;
    }
    du.chuanHoa();
    du.dauCuaSo = (coLaSoAm() == b.coLaSoAm()) ? Duong : Am;

    thuong.chuanHoa();
    thuong.dauCuaSo = (coLaSoAm() == b.coLaSoAm()) ? Duong : Am;
    *this = thuong;
    return *this;
}

/* =========== Vào ra ===============*/
ostream & operator <<(ostream & out, const SNL & snl) {
    snl.Print(out);
    return out;
}

istream & operator >>(istream & in, SNL & snl) {
    string s;
    in >> s;
    snl = SNL(s);
    return in;
}

void SNL::Print(ostream & os) const {
    // SNL được chèn vào luồn os
    os << ToString();
}

/*========== Các toán tử +, - , *, /. ===========*/
SNL operator +(const SNL & a, const SNL & b) {
    SNL ketQua(a);
    ketQua += b;
    return ketQua;
}

SNL operator -(const SNL & a, const SNL & b) {
    SNL ketQua(a);
    ketQua -= b;
    return ketQua;
}

SNL operator *(const SNL & a, const SNL & b) {
    SNL ketQua(a);
    ketQua *= b;
    return ketQua;
}

SNL operator /(const SNL & a, const SNL & b) {
    if (a == SNL(0)) {
        return 0;
    }
    SNL ketQua(a);
    ketQua /= b;
    return ketQua;
}

/* =========== Các toán tử ==, !=, <, >, <=, >=.  ===============*/
bool operator ==(const SNL & a, const SNL & b) {
    return a.Bang(b);
}

bool operator !=(const SNL & a, const SNL & b) {
    return !(a == b);
}

bool operator <(const SNL & a, const SNL & b) {
    return a.nhoHon(b);
}

bool operator >(const SNL & a, const SNL & b) {
    return b < a;
}

bool operator <=(const SNL & a, const SNL & b) {
    return !(a > b);
}

bool operator >=(const SNL & a, const SNL & b) {
    return !(a < b);
}

 /*---------------------------- Xây dựng menu chương trình ------------------------------------*/
void Menu() {
    cout << "CHUONG TRINH TINH TOAN SO NGUYEN LON:\n";
    cout << "============= Menu =============\n";
    cout << "1. Nhap 2 so nguyen lon tu ban phim.\n";
    cout << "2. Nhap 2 so nguyen lon tu file.\n";
    cout << "3. Hien thi 4 phep toan cong, tru, nhan, chia cua 2 so tren ra file.\n";
    cout << "4. Thoat chuong trinh.\n";
}


void case3( SNL soThu_1, SNL soThu_2){
     // Case 3: Hiện thị 4 phép toán +,-,*,/ của 2 số trên ra file output.txt
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
            outputFile << "So thu nhat: " << soThu_1 << '\n';
            outputFile << "So thu hai:  " << soThu_2 << '\n';
            outputFile << "/*----------------------------------------------------------------*/\n";
            outputFile << "Tong cua hai so la: \n"<< soThu_1 <<endl<<" + " <<endl<< soThu_2 <<endl<< " = "<<endl<< (soThu_1 + soThu_2) << '\n';
            outputFile << "/*----------------------------------------------------------------*/\n";
            outputFile << "Hieu cua hai so la: \n" << soThu_1 <<endl<<" - " <<endl<< soThu_2<<endl<< " = " <<endl<< (soThu_1 - soThu_2) << '\n';
            outputFile << "/*----------------------------------------------------------------*/\n";
            outputFile << "Tich cua hai so la: \n" << soThu_1 <<endl<<" * " <<endl<< soThu_2 <<endl<< " = "<<endl<< (soThu_1 * soThu_2) << '\n';
            outputFile << "/*----------------------------------------------------------------*/\n";

            if (soThu_2 != SNL(0))
                outputFile << "Thuong cua hai so la: \n"<<soThu_1 <<endl<<" / " <<endl<< soThu_2 <<endl<< " = " <<endl<< (soThu_1 / soThu_2) <<'\n'<<"Dư" <<" = "<< du;
            else 
                outputFile << "Khong the chia cho so 0.\n";
            
            outputFile.close();
            cout << "Ket qua da duoc ghi vao file output.txt.\n";
    } 
    else
        cout << "Khong the mo file output.txt.\n";
    
} 