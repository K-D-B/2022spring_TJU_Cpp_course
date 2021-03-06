/*************************************
*Author: Kaixu Chen   Moondok
*Date: 2022-07-01 15:08:37
*LastEditTime: 2022-07-01 21:50:12
*Description:
 ***************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<iomanip>
#include<stdlib.h>
using namespace std;

class Time
{
protected:
    long long int h = 0, m = 0, s = 0;
    friend istream& operator >>(istream& i, Time& t);
    friend ostream& operator <<(ostream& o, Time& t);
public:
    Time()
    {}
    Time(int hour, int minute, int second) :h(hour), m(minute), s(second)
    {}
    Time(long long int seconds)
    {
        seconds = seconds % (60 * 60 * 24);
        h = (seconds / (60 * 60));
        seconds -= (h * 3600);
        m = seconds / 60;
        seconds -= m * 60;
        s = seconds;
    }
    Time(const Time& t) :h(t.h), m(t.m), s(t.s)
    {}
    void set(int hour, int minute, int second)
    {
        if (hour + 1)
            h = hour;
        if (minute + 1)
            m = minute;
        if (second + 1)
            s = second;
    }

    void set(long long int seconds)
    {
        seconds = seconds % (60 * 60 * 24);
        h = seconds % (60 * 60);
        seconds -= (h * 3600);
        m = seconds % 60;
        seconds -= m * 60;
        s = seconds;
    }

    Time& operator=(const Time& t)
    {
        this->h = t.h;
        this->m = t.m;
        this->s = t.s;
        return *this;
    }

    Time operator+(long long int seconds)const
    {
        Time tmp(*this);
        seconds = seconds % (3600 * 24);
        long long int extra_h = seconds / (60 * 60);
        seconds -= (extra_h * 3600);
        long long int extra_m = seconds / 60;
        seconds -= extra_m * 60;
        long long int extra_s = seconds;
        tmp.s = (s + extra_s) % 60;
        tmp.m = (m + extra_m + (s + extra_s) / 60) % 60;
        tmp.h = (h + extra_h + (m + extra_m + (s + extra_s) / 60) / 60) % 24;
        return tmp;
    }

    Time operator-(long long int seconds)const
    {
        Time tmp(*this);
        seconds = seconds % (3600 * 24);
        long long int deleted_h = seconds / (60 * 60);
        seconds -= (deleted_h * 3600);
        long long int deleted_m = seconds / 60;
        seconds -= deleted_m * 60;
        long long int deleted_s = seconds;

        if (s - deleted_s >= 0)
            tmp.s = s - deleted_s;
        else
        {
            tmp.s = s + 60 - deleted_s;
            deleted_m += 1;
        }

        if (m - deleted_m >= 0)
        {
            tmp.m = m - deleted_m;
        }
        else
        {
            tmp.m = m + 60 - deleted_m;
            deleted_h += 1;
        }

        if (h - deleted_h >= 0)
            tmp.h = h - deleted_h;
        else
            tmp.h = h + 24 - deleted_h;
        return tmp;
    }

    Time operator++()//??????
    {
        Time tmp(*this);
        if (tmp.s != 59)
            tmp.s++;
        else
        {
            tmp.s = 0;
            if (tmp.m != 59)
                tmp.m++;
            else
            {
                tmp.m = 0;
                if (tmp.h != 23)
                    tmp.h++;
                else
                    tmp.h = 0;
            }
        }
        *this = tmp;//???????????????
        return tmp;
    }

    Time operator++(int i)//??????
    {
        Time tmp(*this);
        if (tmp.s != 59)
            tmp.s++;
        else
        {
            tmp.s = 0;
            if (tmp.m != 59)
                tmp.m++;
            else
            {
                tmp.m = 0;
                if (tmp.h != 23)
                    tmp.h++;
                else
                    tmp.h = 0;
            }
        }
        return tmp;
    }

    Time operator--()
    {
        Time tmp(*this);
        if (tmp.s != 0)
            tmp.s--;
        else
        {
            tmp.s = 59;
            if (tmp.m != 0)
                tmp.m--;
            else
            {
                tmp.m = 59;
                if (tmp.h != 0)
                    tmp.h--;
                else
                    tmp.h = 23;
            }
        }
        *this = tmp;//???????????????
        return tmp;
    }

    Time operator--(int i)
    {
        Time tmp(*this);
        if (tmp.s != 0)
            tmp.s--;
        else
        {
            tmp.s = 59;
            if (tmp.m != 0)
                tmp.m--;
            else
            {
                tmp.m = 59;
                if (tmp.h != 0)
                    tmp.h--;
                else
                    tmp.h = 23;
            }
        }
        return tmp;
    }

    bool operator>(const Time& t) const
    {
        return (h > t.h || (h == t.h && m > t.m) || (h == t.h && m == t.m && s > t.s));
    }

    bool operator<(const Time& t) const
    {
        return (h < t.h || (h == t.h && m < t.m) || (h == t.h && m == t.m && s < t.s));
    }

    bool operator==(const Time& t)const
    {
        return (h == t.h && m == t.m && s == t.s);
    }

    bool operator!=(const Time& t)const
    {
        return !(*this == t);
    }

    bool operator >=(const Time& t) const
    {
        return !(*this < t);
    }

    bool operator <=(const Time& t) const
    {
        return !(*this > t);
    }



};

istream& operator >>(istream& i, Time& t)
{
    i >> t.h >> t.m >> t.s;
    return i;
}

ostream& operator <<(ostream& o, Time& t)
{
    o << t.h << ":" << t.m << ":" << t.s << endl;
    return o;
}


bool is_leap(const int year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}



class Date
{
protected:
    friend Date operator +(const Date& a, const int b);
    friend Date operator +(const int b, const Date& a);
    friend Date operator -(const Date& a, const int b);

    friend ostream& operator <<(ostream& o, Date& d);
    friend istream& operator>>(istream& i, Date& d);
    int year;
    int month;
    int day;
public:
    Date()
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        year = ltm->tm_year + 1900;
        month = ltm->tm_mon + 1;
        day = ltm->tm_mday;
    }
    Date(const int y, const int m, const int d) :year(y), month(m), day(d)
    {}

    //????????????
    Date(int d)
    {
        if (d >= 0)
        {
            int tmp = d;
            int i = 1900; //i????????????
            while (tmp > 365 + is_leap(i))
            {
                tmp -= (365 + is_leap(i));
                i++;
            }
            year = i;
            int j = 1;
            int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
            while (tmp > month_table[j])
            {
                tmp -= month_table[j];
                j++;
            }
            month = j;
            day = tmp;
        }
        else
        {
            int tmp = d;
            int i = 1900;
            while (tmp < 0)  //????????????d???????????????
            {
                i--;
                tmp += (365 + is_leap(i));

            }
            year = i;
            //????????????i???1???1??????????????????tmp????????????0?????????????????????1???????????????????????????????????????????????????
            //?????????tmp?????????1
            tmp++;
            int j = 1;
            int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
            while (tmp > month_table[j])
            {
                j++;
                tmp -= month_table[j];
            }
            month = j;
            day = tmp;
        }
    }

    //??????????????????
    explicit operator int()
    {
        int tmp = 0;
        int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
        if (this->year >= 1900)  //??????tmp?????????
        {
            for (int i = 1900; i < this->year; i++)
                tmp += 365 + is_leap(i);
            //????????????

            for (int i = 1; i < this->month; i++)
                tmp += month_table[i];

            //????????????
            tmp += this->day;
        }
        else  //??????tmp?????????
        {
            //???????????????1???????????????
            tmp += month_table[this->month] - this->day + 1;
            //??????????????????1???????????????
            for (int i = this->month + 1; i <= 12; i++)
                tmp += month_table[i];
            //??????????????????????????????1900????????????
            for (int i = this->year + 1; i < 1900; i++)
                tmp += 365 + is_leap(i);
            //?????????????????????1900??????????????????
            tmp = -tmp;

        }
        return tmp;

    }

    void set(int y, int m = 1, int d = 1)
    {
        if (y)
            year = y;
        if (m)
            month = m;
        if (d)
            day = d;
    }

    Date& operator++ ()
    {
        int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
        if (this->day == month_table[this->month])
        {
            if (this->month == 12)
            {
                Date::set(this->year + 1, 1, 1);
            }
            else
                Date::set(this->year, this->month + 1, 1);
        }
        else
            this->day++;
        return *this;
    }

    Date& operator-- ()
    {
        int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
        if (this->day == 1)
        {
            if (this->month == 1)
            {
                Date::set(this->year - 1, 12, 31);
            }
            else
                Date::set(this->year, this->month - 1, month_table[this->month - 1]);
        }
        else
            this->day--;
        return *this;
    }

    Date operator++(int)
    {
        int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
        Date tmp(this->year, this->month, this->day);
        if (this->day == month_table[this->month])
        {
            if (tmp.month == 12)
            {
                Date::set(this->year + 1, 1, 1);
            }
            else
                Date::set(this->year, this->month + 1, 1);
        }
        else
            Date::set(this->year, this->month, this->day + 1);

        return tmp;
    }

    Date operator--(int)
    {
        int month_table[13] = { -1,31,28 + is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31 };
        Date tmp(this->year, this->month, this->day);
        if (this->day == 1)
        {
            if (this->month == 1)
            {
                Date::set(this->year - 1, 12, 31);
            }
            else
                Date::set(this->year, this->month - 1, month_table[this->month - 1]);
        }
        else
            Date::set(this->year, this->month, this->day - 1);

        return tmp;
    }

    bool operator>(const Date& b)const
    {
        if (this->year > b.year)
            return true;
        if (this->month > b.month)
            return true;
        if (this->day > b.day)
            return true;

        return false;
    }
    bool operator<(const Date& b)const
    {
        if (this->year < b.year)
            return true;
        if (this->month < b.month)
            return true;
        if (this->day < b.day)
            return true;

        return false;
    }


    bool operator>=(const Date& b)const
    {
        return !(*this < b);
    }


    bool operator<=(const Date& b)const
    {

        return !(*this > b);
    }

    bool operator==(const Date& b)const
    {
        if (this->year == b.year && this->month == b.month && this->day == b.day)
            return true;
        return false;
    }

    bool operator!=(const Date& b)const
    {
        return !(*this == b);
    }

    Date& operator+=(const int b)
    {
        Date tmp = *this + b;
        Date::set(tmp.year, tmp.month, tmp.day);
        return *this;
    }

    Date& operator-=(const int b)
    {
        Date tmp = *this - b;
        Date::set(tmp.year, tmp.month, tmp.day);
        return *this;
    }

};


ostream& operator <<(ostream& o, Date& d)  //??????????????????
{
    o << d.year << "???" << d.month << "???" << d.day << "???" << endl;
    return o;
}

istream& operator>>(istream& i, Date& d)  //??????????????????
{
    i >> d.year >> d.month >> d.day;
    return i;
}

Date operator +(const Date& a, const int b)//+??????????????????
{
    if (b >= 0)
    {
        Date tmp;
        int tem = b;
        int month_table[13] = { -1,31,28 + is_leap(a.year),31,30,31,30,
                             31,31,30,31,30,31 };
        int i = a.year;
        int j = a.month;
        int k = a.day;
        if (tem > month_table[a.month] - a.day)  //?????????
        {
            if (j != 12)
            {
                j++;
            }
            else
            {
                i++;
                j = 1;

            }
            k = 1;
            tem -= (month_table[a.month] - a.day);//???-1?????????????????????????????????1???????????????1?????????????????????

            //?????????i?????????????????????
            while (tem > month_table[j] && j <= 12)
            {
                tem -= month_table[j];
                j++;
            }

            if (j == 13) //???i???????????????
            {
                j = 1;
                i++;
                while (tem > 365 + is_leap(i))
                {
                    tem -= (365 + is_leap(i));
                    i++;
                }

                int j = 1;
                int month_table[13] = { -1,31,28 + is_leap(i),31,30,31,30,
                             31,31,30,31,30,31 };
                while (tem > month_table[j])
                {
                    tem -= month_table[j];
                    j++;
                }
                tmp.set(i, j, tem);
                return tmp;

            }
            else
            {
                tmp.set(i, j, tem);
                return tmp;
            }

        }
        else
        {
            tmp.set(i, j, k - b);
            return tmp;
        }

    }
    else
        return a - b;
}

Date operator +(const int b, const Date& a)
{
    return a + b;
}

Date operator -(const Date& a, const int b)
{
    if (b > 0)
    {
        if (a.day > b)  //???????????????
        {
            Date tmp(a.year, a.month, a.day - b);
            return tmp;
        }
        else//????????????
        {
            int i = a.year;
            int j = a.month;

            int tem = b;

            tem -= (a.day - 1);  //???????????????1???
            if (j == 1)
            {
                j = 12;
                i--;
            }
            else
                j--;

            int month_table[13] = { -1,31,28 + is_leap(i),31,30,31,30,
                             31,31,30,31,30,31 };
            while (tem > month_table[j] && j >= 1)
            {
                tem -= month_table[j];
                j--;

            }
            if (j == 0)  //????????????????????????
            {
                i--;
                int tmp = -tem;
                while (tmp < 0)  //????????????d???????????????
                {
                    tmp += (365 + is_leap(i));
                    if (tmp >= 0)
                        break;
                    i--;
                }

                //????????????i???1???1??????????????????tmp????????????0?????????????????????1???????????????????????????????????????????????????
                //?????????tmp?????????1
                tmp++;
                int j = 1;
                int month_table[13] = { -1,31,28 + is_leap(i),31,30,31,30,
                             31,31,30,31,30,31 };
                while (tmp > month_table[j])
                {
                    tmp -= month_table[j];
                    j++;
                }
                return Date(i, j, tmp);
            }
            else
            {
                return Date(i, j, month_table[j] - tem + 1);
            }

        }
    }
    else
        return a + (-b);
}

int operator -(Date a, Date b)
{
    int d1 = (int)a;
    int d2 = (int)b;
    return d1 - d2;
}



class DateTime :public Date, public Time
{
private:
    friend ostream& operator<<(ostream& o, DateTime& a);
    friend istream& operator>>(istream& i, DateTime& a);
public:
    DateTime() :Date(1900, 1, 1), Time(0, 0, 0)
    {}
    DateTime(int hour, int minute, int second) :Date(1900, 1, 1), Time(hour, minute, second)
    {}
    DateTime(int year, int month, int day, int hour, int minute, int second) :
        Date(year, month, day), Time(hour, minute, second) {}

    DateTime(long long int seconds) :Date(int(seconds / (24 * 60 * 60) + 1)), Time((seconds % (24 * 60 * 60)))
    {}  //????????????????????????1?????????????????????1900.1.1????????????????????????????????????

    void set(int y, int mon, int d, int hour, int minute, int second)
    {
        if (y + 1)
            year = y;
        if (mon + 1)
            month = mon;
        if (d + 1)
            day = d;
        if (hour + 1)
            h = hour;
        if (minute + 1)
            m = minute;

        if (day + 1)
            d = day;
        if (second + 1)
            s = second;
    }

    void set(int y, int mon, int d)
    {
        if (y + 1)
            year = y;
        if (mon + 1)
            month = mon;
        if (d + 1)
            day = d;
    }

    void set(long long seconds)
    {
        set(1900, 1, 1, 0, 0, 0);
        *this = operator+(seconds);

    }

    bool operator>(const DateTime& t)const
    {
        return (year > t.year || (year == t.year && month > t.month) || (year == t.year && month == t.month && day > t.day) ||
            (year == t.year && month == t.month && day == t.day && h > t.h) ||
            (year == t.year && month == t.month && day == t.day && h == t.h && m > t.m) ||
            (year == t.year && month == t.month && day == t.day && h == t.h && m == t.m && s > t.s));

    }

    bool operator<=(const DateTime& t)const
    {
        return !(*this > t);
    }

    bool operator<(const DateTime& t)const
    {
        return (year < t.year || (year == t.year && month < t.month) || (year == t.year && month == t.month && day < t.day) ||
            (year == t.year && month == t.month && day == t.day && h < t.h) ||
            (year == t.year && month == t.month && day == t.day && h == t.h && m < t.m) ||
            (year == t.year && month == t.month && day == t.day && h == t.h && m == t.m && s < t.s));

    }

    bool operator>=(const DateTime& t)const
    {
        return !(*this < t);
    }

    bool operator==(const DateTime& t)const
    {
        return (year == t.year && month == t.month && day == t.day && h == t.h && m == t.m && s == t.s);
    }

    bool operator!=(const DateTime& t)const
    {
        return !(*this == t);
    }

    DateTime operator++()
    {
        DateTime tmp(*this);
        if (tmp.s != 59)
            tmp.s++;
        else
        {
            tmp.s = 0;
            if (tmp.m != 59)
                tmp.m++;
            else
            {
                tmp.m = 0;
                if (tmp.h != 23)
                    tmp.h++;
                else
                {
                    tmp.h = 0;
                    Date::operator++();
                }
            }
        }
        *this = tmp;//???????????????
        return tmp;
    }

    DateTime operator++(int i)
    {
        DateTime tmp(*this);
        if (s != 59)
            s++;
        else
        {
            s = 0;
            if (m != 59)
                m++;
            else
            {
                m = 0;
                if (h != 23)
                    h++;
                else
                {
                    h = 0;
                    Date::operator++(i);
                }
            }
        }
        return tmp;
    }

    DateTime operator--()
    {
        DateTime tmp(*this);
        if (tmp.s != 0)
            tmp.s--;
        else
        {
            tmp.s = 59;
            if (tmp.m != 0)
                tmp.m--;
            else
            {
                tmp.m = 59;
                if (tmp.h != 0)
                    tmp.h--;
                else
                {
                    tmp.h = 23;
                    Date::operator--();
                }
            }
        }
        *this = tmp;//???????????????
        return tmp;
    }

    DateTime operator--(int i)
    {
        DateTime tmp(*this);
        if (s != 0)
            s--;
        else
        {
            s = 59;
            if (m != 0)
                m--;
            else
            {
                m = 59;
                if (h != 0)
                    h--;
                else
                {
                    h = 23;
                    Date::operator--(i);
                }
            }
        }
        return tmp;
    }

    DateTime& operator=(const DateTime& t)
    {
        year = t.year;
        month = t.month;
        day = t.day;
        h = t.h;
        m = t.m;
        s = t.s;
        return *this;
    }

    DateTime operator+(long long int seconds)
    {
        DateTime tmp(*this);
        long long int extra_day = seconds / (3600 * 24);
        seconds = seconds % (3600 * 24);
        long long int extra_h = seconds / (60 * 60);
        seconds -= (extra_h * 3600);
        long long int extra_m = seconds / 60;
        seconds -= extra_m * 60;
        long long int extra_s = seconds;
        tmp.s = (s + extra_s) % 60;
        tmp.m = (m + extra_m + (s + extra_s) / 60) % 60;
        tmp.h = (h + extra_h + (m + extra_m + (s + extra_s) / 60) / 60) % 24;
        extra_day += (h + extra_h + (m + extra_m + (s + extra_s) / 60) / 60) / 24;
        tmp.Date::operator+=(int(extra_day));
        return tmp;
    }

    DateTime operator-(long long int seconds)
    {
        DateTime tmp(*this);
        long long int extra_day = seconds / (3600 * 24);
        seconds = seconds % (3600 * 24);
        long long int deleted_h = seconds / (60 * 60);
        seconds -= (deleted_h * 3600);
        long long int deleted_m = seconds / 60;
        seconds -= deleted_m * 60;
        long long int deleted_s = seconds;

        if (s - deleted_s >= 0)
            tmp.s = s - deleted_s;
        else
        {
            tmp.s = s + 60 - deleted_s;
            deleted_m += 1;
        }

        if (m - deleted_m >= 0)
        {
            tmp.m = m - deleted_m;
        }
        else
        {
            tmp.m = m + 60 - deleted_m;
            deleted_h += 1;
        }

        if (h - deleted_h >= 0)
            tmp.h = h - deleted_h;
        else
        {
            tmp.h = h + 24 - deleted_h;
            extra_day++;
        }
        tmp.Date::operator-=(int(extra_day));
        return tmp;
    }

};
ostream& operator<<(ostream& o, DateTime& a)
{
    o << a.year << "." << a.month << "." << a.day << " " << setfill('0') << setw(2) << a.h << ":" << setfill('0') << setw(2) << setfill('0') << a.m << ":" << setfill('0') << setw(2) << a.s << endl;
    return o;
}
istream& operator>>(istream& i, DateTime& a)
{
    i >> a.year >> a.month >> a.day >> a.h >> a.m >> a.s;
    return i;
}


int main()
{
    cout << "????????????????????????" << endl;
    {
        DateTime t1;                           // 1900???1???1??? 00:00:00
        cout << t1;
        DateTime t2(1, 2, 3);                  // 1900???1???1??? 01:02:03
        cout << t2;
        DateTime t3(1980, 12, 31, 12, 23, 34); // 1980???12???31??? 12:23:34
        cout << t3;
        DateTime t4(123);                      // 1900???1???1??? 00:02:03
        cout << t4;
    }
    cout << endl;

    cout << "??????set??????" << endl;
    {
        DateTime t1;
        t1.set(1980, 12, 31, 20, 14, 13);  // 1980???12???31??? 20:14:13
        cout << t1;
        t1.set(2000, 2, 29);               // 2000???2???29??? 20:14:13
        cout << t1;
        t1.set(-1, -1, -1, -1, 13, 14);    // 2000???2???29??? 20:13:14
        cout << t1;
        t1.set(3768726214);                // 2019???6???5??? 12:23:34
        cout << t1;
    }

    cout << "??????+???-" << endl;
    {
        DateTime t1(1987, 2, 20, 2, 34, 25), t2(2001, 3, 30, 23, 45, 45), t3(2001, 12, 18, 17, 23, 27), t4, t5, t6;
        t4 = t1.operator+(52435243);
        cout << "t4?????????: 1988.10.18 23:55:08" << "?????????:" << t4;
        t5 = t2.operator-(300000000);
        cout << "t5?????????: 1991.9.27 18:25:45" << "?????????:" << t5;
        t6 = t3.operator+(500000000);
        cout << "t6?????????: 2017.10.22 18:16:47" << "?????????:" << t6;
    }

    cout << endl;
    cout << "??????++???--" << endl;
    {
        DateTime t1(2000, 12, 31, 23, 59, 59), t2(2000, 12, 30, 22, 15, 16), t3(2001, 1, 1, 0, 0, 0);
        DateTime t5 = t2;
        t1++;
        cout << "??????1s??????t1?????????2001.1.1 00:00:00???????????????" << (t1);
        t3--;
        cout << "??????1s??????t3?????????2000.12.31 23:59:59???????????????" << (t3);
        --t2;
        cout << "??????1s??????t2?????????2000.12.30 22:15:15???????????????" << (t2);
        ++t5;
        cout << "??????1s??????t5?????????2000.12.30 22:15:17???????????????" << (t5);

    }
    cout << endl;
    cout << "???????????????????????????" << endl;
    {
        DateTime t1(2000, 3, 1, 20, 34, 35), t2(2000, 3, 1, 19, 34, 35), t3(2000, 3, 1, 20, 34, 35);
        cout << "t1>t2???????????????1,?????????" << (t1 > t2) << endl;
        cout << "t1<t2???????????????0,?????????" << (t1 < t2) << endl;
        cout << "t1==t3???????????????1,?????????" << (t1 == t3) << endl;
        cout << "t1!=t3???????????????0,?????????" << (t1 != t3) << endl;
        cout << "t2>=t3???????????????0,?????????" << (t2 >= t3) << endl;
        cout << "t2<=t3???????????????1,?????????" << (t2 <= t3) << endl;
    }
    return 0;
}
