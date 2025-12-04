/*----------------------------------------------------------------*/
// Name: Tạ Thị Nga
// Student ID: 20227026
// Class: Toán Tin 02 - K67
// Project: Chủ đề 2: Xây dựng "thư viện" phép toán với số nguyên lớn
// Date: 20/06/2024
/*-----------------------------------------------------------------*/

#ifndef SNL_H
#define SNL_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <cfloat>
#include <stdexcept>
#include <fstream>

using namespace std;

enum Dau { Duong, Am }; //trạng thái số âm - Am, số dương - Duong

// SNL là đại diện cho số nguyên lớn
class SNL {

    private:
        vector<char> soNguyenLon;
        Dau dauCuaSo; // biến lưu dấu của số
        int chuSoNguyenLon;
        //SNL du;

    public:
        SNL();
        SNL(int num); // num ở đây là một số nguyên
        SNL(const string & s);
        SNL(const SNL & rhs) = default; 
        
        bool coLaSoAm() const;
        bool coLaSoDuong() const;
        int soChuSo() const;
        int layChuSo(int) const;
        void themChuSo(int);
        void thayDoiChuSo(int, int );
        void chuanHoa();

        void Print(ostream & os) const;

        string ToString() const;
        int ToInt() const;
        double ToDouble() const;
        
        bool Bang(const SNL &) const;
        bool nhoHon(const SNL &) const;
        
        const SNL & operator +=(const SNL & );
        const SNL & operator -=(const SNL & );
        const SNL & operator *=(const SNL & );
        const SNL & operator *=(int );
        const SNL & operator /=(const SNL & );

        friend ostream & operator <<(ostream & out, const SNL & );
        friend istream & operator >>(istream & in, SNL & );

        friend SNL operator +(const SNL &, const SNL & );
        friend SNL operator -(const SNL &, const SNL & );
        friend SNL operator *(const SNL &, const SNL & );
        friend SNL operator /(const SNL &, const SNL & );

        friend bool operator ==(const SNL &, const SNL &);
        friend bool operator !=(const SNL &, const SNL &);
        friend bool operator <(const SNL &, const SNL & );
        friend bool operator >(const SNL &, const SNL & );
        friend bool operator <=(const SNL &, const SNL & );
        friend bool operator >=(const SNL &, const SNL & );

};

#endif // SNL_H
