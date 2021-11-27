#include <iostream>
#include "clock_time.h"
using namespace std;

clock_time::clock_time(int h, int m, int s){
    set_time(h,m,s);
}
clock_time::clock_time(){
    set_time(0,0,0);
}

int clock_time::get_hour(){
    return (_time/3600);
}

int clock_time::get_minute(){
    return ((_time % 3600) / 60);
}

int clock_time::get_second(){
    return (_time % 60);
}

void clock_time::set_time(int h, int m, int s){
    _time += (3600*h) + (60*m) + s;
}

string to_string(clock_time c){
    string h = "";
    string m = "";
    string s = "";
    if(c.get_hour() < 10){
        h = "0" + to_string(c.get_hour());
    }else{
        h = to_string(c.get_hour());
    }
    if(c.get_minute() < 10){
        m = "0" + to_string(c.get_minute());
    }else{
        m = to_string(c.get_minute());
    }
    if(c.get_second() < 10){
        s = "0" + to_string(c.get_second());
    }else{
        s = to_string(c.get_second());
    }
    return (h + ":" + m + ":" + s);

}

ostream& operator<<(ostream& out, clock_time c){
    out << to_string(c);
}

bool operator ==(clock_time a, clock_time b){
    return a._time == b._time;
}

bool operator !=(clock_time a, clock_time b){
    return a == b;
}

int operator +(clock_time a, clock_time b){
    return a._time + b._time;
}

