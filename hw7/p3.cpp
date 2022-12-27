// author: R10521802

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAX_LENGTH = 100;
const int YEAR = 2022;
const int MONTH = 11;
const int DATE = 1;

struct Member {
    char* name;
    int year;
    int month;
    int date;
    char* phone;
    bool qualified = false;
    char* getLastname();
    int getAgeDays();
};


// Don't know if this would lead to memory leak🥺🥺🥺
char* Member::getLastname() {
    char* fullname = new char[MAX_LENGTH];
    strcpy(fullname, name);
    char* lastname = strtok(fullname, " ");
    lastname = strtok(NULL, " ");
    delete [] fullname;
    return lastname;
}

int Member::getAgeDays() {
    return (YEAR - year) * 365 + (MONTH - month) * 30 + (DATE - date) + 1;
}

// read members info from file
void readMembers(int n, Member* members, char** data) {
    for (int i = 0; i < n; i++) {
        data[i] = new char[MAX_LENGTH];
        cin.getline(data[i], MAX_LENGTH);
        char delim[] = ",/";
        members[i].name = strtok(data[i], delim);
        members[i].year = atoi(strtok(NULL, delim));
        members[i].month = atoi(strtok(NULL, delim));
        members[i].date = atoi(strtok(NULL, delim));
        members[i].phone = strtok(NULL, delim);
    }
}

// check if member is old enough
bool oldEnough(int memberDays, int year) {
    return memberDays >= year * 365;
}

// check if member's phone number is valid
bool samePhoneNo(char* memberPhone, char* x) {
    char phoneNo[5];
    strncpy(phoneNo, memberPhone, 4);
    return strcmp(phoneNo, x) == 0;
}

// get the number of qualified members
int numQualified(Member* members, int nMembers, int year, int c, char x[4]) {
    int count = 0;
    for (int i = 0; i < nMembers; i++) {
        if (c == 1 && oldEnough(members[i].getAgeDays(), year)) {
            members[i].qualified = true;
            count++;
        }
        else if (c == 2 && samePhoneNo(members[i].phone, x)) {
            members[i].qualified = true;
            count++;
        }
        else if (c == 3 && (oldEnough(members[i].getAgeDays(), year) || samePhoneNo(members[i].phone, x))) {
            members[i].qualified = true;
            count++;
        }
        else if (c == 4 && oldEnough(members[i].getAgeDays(), year) && samePhoneNo(members[i].phone, x)) {
            members[i].qualified = true;
            count++;
        }
    }
    return count;
}

// get the final member's name
char* oldestMember(Member* members, int n) {
    int oldest = 0;
    for (int i = 0; i < n; i++) {
        if (!members[i].qualified) {
            continue;
        }
        bool isOlder = members[i].getAgeDays() > members[oldest].getAgeDays();
        if (isOlder || (members[i].getAgeDays() == members[oldest].getAgeDays() && strcmp(members[i].getLastname(), members[oldest].getLastname()) < 0)) {
            oldest = i;
        }
    }
    return members[oldest].name;
}

int main() {
    int n, c, t;
    char x[4];
    cin >> n >> c >> t;
    cin >> x;
    cin.ignore();
    Member* members = new Member[n];
    char** data = new char*[n];

    readMembers(n, members, data);

    int numQ = numQualified(members, n, t, c, x);
    if (numQ == 0) {
        cout << 0;
        return 0;
    }
    else if (numQ == 1) {
        for (int i = 0; i < n; i++) {
            if (members[i].qualified) 
                cout << members[i].name << "," << numQ;
        }
    }
    else cout << oldestMember(members, n) << "," << numQ;

    // release memory
    delete [] members;
    members = nullptr;
    for (int i = 0; i < n; i++) {
        delete [] data[i];
        data[i] = nullptr;
    }
    delete [] data;
    data = nullptr;
    return 0;
}