#include<iostream>
#include<string>
#include<map>
#include<iomanip>

using namespace std;

int startDayInJanuary = 3;
int startYear = 1919;
int startMonth = 1;

map<int, string> DaysOnWeek{
    pair<int,string>{1, "��"},
    pair<int,string>{2, "��"},
    pair<int,string>{3, "��"},
    pair<int,string>{4, "��"},
    pair<int,string>{5, "��"},
    pair<int,string>{6, "��"},
    pair<int,string>{7, "��"}
};

map<int,string> MonthOnYear{
    pair<int,string>{1,"������"},
    pair<int,string>{2,"�������"},
    pair<int,string>{3,"����"},
    pair<int,string>{4,"������"},
    pair<int,string>{5,"���"},
    pair<int,string>{6,"����"},
    pair<int,string>{7,"����"},
    pair<int,string>{8,"������"},
    pair<int,string>{9,"��������"},
    pair<int,string>{10,"�������"},
    pair<int,string>{11,"������"},
    pair<int,string>{12,"�������"}
};

map<int,int> DaysInMonth{
    pair<int,int>(1, 31),
    pair<int,int>(2, 28),
    pair<int,int>(3, 31),
    pair<int,int>(4, 30),
    pair<int,int>(5, 31),
    pair<int,int>(6, 30),
    pair<int,int>(7, 31),
    pair<int,int>(8, 31),
    pair<int,int>(9, 30),
    pair<int,int>(10, 31),
    pair<int,int>(11, 30),
    pair<int,int>(12, 31),
};

bool isRegularYear(int year){
    if (year % 4 == 0 && year % 100 != 0){
        return false;
    }else if (year % 400 == 0){
        return false;
    }
    return true;
}
int foundRange(int countRepeats){
    startYear += 11;
    countRepeats++;
    if (countRepeats == 4){
        countRepeats = 0;
        startDayInJanuary -= 1;
        if (startDayInJanuary == 0){
            startDayInJanuary = 7;
        }
    }
    return countRepeats;
}
void foundFirstDayJanuary(){
    bool isRegular = isRegularYear(startYear);
        if (isRegular){
            startDayInJanuary++;
        }else {
            startDayInJanuary += 2;
        }

        if (startDayInJanuary > 7){
            startDayInJanuary = startDayInJanuary % 7;
        }

        startYear++;
}
void foundFirstDaySelectedMonth(){
    bool isRegular = isRegularYear(startYear);
    startDayInJanuary += DaysInMonth[startMonth];
    if (startMonth == 2 && !isRegular){
        startDayInJanuary += 1;
    }
    startMonth++;  
}
int foundFirstDayMonth(int month, int year){
    int countRepeats = 1;
    while (startYear + 11 <= year){
        countRepeats = foundRange(countRepeats);
    } 
    while (startYear < year){
        foundFirstDayJanuary();
    }
    while (startMonth < month){
        foundFirstDaySelectedMonth();
    }
    int dayNumber = startDayInJanuary % 7;
    if (dayNumber == 0){
        dayNumber = 7;
    }
    return dayNumber;
}

int validationYear(string year){
    int validationYear = 0;
    validationYear = atoi(year.c_str());
    if (validationYear == 0){
        cout << "��� ����� ���� �� ������ ���� ��������� ��������!" << endl;
        return -1;
    }else if (validationYear < 1919 || validationYear > 2069){
        cout << "������ ������� ��� ������ 1919 ��� ����� 2069!" << endl;
        return -1;
    }
    return validationYear;
}

int validationMonth(string month){
    int validationMonth = 0;
    validationMonth = atoi(month.c_str());
    if (validationMonth == 0){
        cout << "��� ����� ������ �� ������ ���� ��������� ��������!" << endl;
        return -1;
    }else if (validationMonth < 1 || validationMonth > 12){
        cout << "����� �� ����� ���� ������ 1 ��� ������ 12!" << endl;
        return -1;
    }
    return validationMonth;
}

void printMonth(int year, int month){
    int startDay = foundFirstDayMonth(month, year);
    int countDay = 0;
    int countDaysInMonth = DaysInMonth[month];
    bool isRegular = isRegularYear(year);
    bool isWriting = false;
    if (month == 2 && !isRegular){
        countDaysInMonth += 1;
    }
    cout << MonthOnYear[month] << ' ' << year << endl;
    for(const auto& day: DaysOnWeek){
        cout << setw(5) << day.second;
    }
    cout << endl;
    for(int i = 1; i <= countDaysInMonth; i++){
        countDay++;
        if (i == startDay && !isWriting){
            isWriting = true;
            i = 1;
        }
        if (!isWriting){
            cout << setw(5) << ' ';
        }
        if(isWriting){
            cout << setw(5) << i;
            if (countDay == 7){
                cout << endl;
                countDay = 0;
            }
        }
    }
}

int main(){
    cout << setiosflags(ios::left);
    string month, year = "";
    int validMonth, validYear = 0;
    cout << "������ ��������� ������� ��������� ������, ������� �� ������� � ���� ����, ������� �� �������.\n��������� �������� �����: 1919-2069." << endl;
    cout << "������� �����: ";
    cin >> month;
    validMonth = validationMonth(month);
    if (validMonth < 0){
        cout << "����� ������ ���������!";
        return 0;
    }
    cout << "������� ���: ";
    cin >> year;
    validYear = validationYear(year);
    if (validYear > 0 && validMonth > 0){
        cout << endl;
        printMonth(validYear, validMonth);
    }
    cout << endl << endl << "����� ������ ���������!";
    return 0;
}