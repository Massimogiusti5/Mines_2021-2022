#pragma once
using namespace std;

class clock_time{
    public:
        friend bool operator ==(clock_time a, clock_time b);
        friend int operator +(clock_time a, clock_time b);
        int get_hour();
        int get_minute();
        int get_second();
        void set_time(int h, int m, int s);
        clock_time();
        clock_time(int h, int m, int s);
        friend ostream& operator<<(ostream & out, clock_time c);
    private:
        int _time;
};

