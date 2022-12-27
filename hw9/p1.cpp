// author: R10521802

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LENGTH = 50+1;

class Member {
    private:
        int ID;
        char* name;
        int lastVisit;
        int avgMonthlyExp;
        static int lostThreshold;
    public:
        Member();
        Member(int ID, char* name, int lastVisit, int avgMonthlyExp);
        ~Member();
        char* getName() { return name; }
        bool isLost() const;
        bool operator>(const Member& m) const;
};

int Member::lostThreshold = 12;

Member::Member() {
    ID = 0;
    name = nullptr;
    lastVisit = 0;
    avgMonthlyExp = 0;
}

Member::Member(int ID, char* name, int lastVisit, int avgMonthlyExp) {
    this->ID = ID;
    this->lastVisit = lastVisit;
    this->avgMonthlyExp = avgMonthlyExp;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Member::~Member() {
    delete [] name;
    name = nullptr;
}

bool Member::isLost() const {
    return this->lastVisit > Member::lostThreshold;
}
bool Member::operator>(const Member& m) const {
    if(this->isLost())  // the order of lost members is not important
        return false;
    else if(this->lastVisit > m.lastVisit || m.isLost())
        return true;
    else if(this->lastVisit == m.lastVisit && this->avgMonthlyExp > m.avgMonthlyExp)
        return true;
    else if(this->lastVisit == m.lastVisit && this->avgMonthlyExp == m.avgMonthlyExp && this->ID < m.ID)
        return true;
    else
        return false;
}


int activeMemberCnt(Member** members, int memberCnt) {
    int cnt = 0;
    for(int i = 0; i < memberCnt; i++) {
        if(members[i]->isLost() == false)
            cnt ++;
    }
    return cnt;
}

// swap the two members in the array
void swap(Member*& ptr1, Member*& ptr2) {
    Member* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

// sort the array according to last visited time and the average consumption
void sortMember(Member** members, int nMembers) {
    for (int i = 0; i < nMembers; i++) {
        for (int j = i; j > 0; j--) {
            if (*members[j] > *members[j - 1]) {
                swap(members[j], members[j - 1]);
            }
            else break;
        }
    }    
}

void readInput(Member** members, int n) {
    char* nameData = new char[MAX_LENGTH*n];
    int* lastVisited = new int[n];
    int* avgConsump = new int[n];
    cin.ignore();
    cin.getline(nameData, MAX_LENGTH*n);
    for (int i = 0; i < n; i++) cin >> lastVisited[i];
    for (int i = 0; i < n; i++) cin >> avgConsump[i];
    char delim[] = ",";
    char* name = strtok(nameData, delim);
    for (int i = 0; i < n; i++) {
        members[i] = new Member(i + 1, name, lastVisited[i], avgConsump[i]);
        name = strtok(NULL, delim);
    }

    delete[] nameData;
    delete[] lastVisited;
    delete[] avgConsump;
}

int main() {
    int n, m;
    cin >> n >> m;
    Member** members = new Member*[n];
    readInput(members, n);
    sortMember(members, n);
    int activeCnt = activeMemberCnt(members, n);
    for (int i = 0; i < min(m, activeCnt); i++) 
        i != min(m, activeCnt)-1 ? cout << members[i]->getName() << "," : cout << members[i]->getName();

    for (int i = 0; i < n; i++) delete members[i];
    delete[] members;
}