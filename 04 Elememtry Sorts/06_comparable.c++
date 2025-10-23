#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Date {
    int year;
    int month;
    int day;

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

bool dateCmp(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

int main() {
    vector<Date> dates = {
        {2023, 5, 1},
        {2022, 12, 30},
        {2023, 1, 15}
    };

    cout << "compare with operator< :\n";
    sort(dates.begin(), dates.end());  
    for (const auto& d : dates)
        cout << d.year << "/" << d.month << "/" << d.day << "\n";

    cout << "\ncompare with function :\n";
    sort(dates.begin(), dates.end(), dateCmp); 
    for (const auto& d : dates)
        cout << d.year << "/" << d.month << "/" << d.day << "\n";

    return 0;
}