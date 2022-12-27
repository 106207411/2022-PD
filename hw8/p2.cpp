// author: R10521802

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LENGTH = 50;

class Member {
    private:
        int ID;
        char* name;
        int lastVisit;
        int avgMonthlyExp;
    public:
        Member();
        Member(int ID, char* name, int lastVisit, int avgMonthlyExp);
        ~Member();
        int getID() { return ID; }
        int getLastVisit() { return lastVisit; }
        int getAvgMonthlyExp() { return avgMonthlyExp; }
        char* getName() { return name; }
};

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
    this->name = new char[MAX_LENGTH+1];
    strcpy(this->name, name);
}

Member::~Member() {
    delete [] name;
}


// exclude the member in the array if last visited time > 12
// update the number of remaining members
void excludeMember(Member** members, int& nMembers) {
    int i = 0;
    while (i < nMembers) {
        if (members[i]->getLastVisit() > 12) {
            for (int j = i; j < nMembers - 1; j++) {
                members[j] = members[j + 1];
            }
            nMembers--;
        }
        else i++;
    }
}

// swap the two members in the array
void swap(Member** members, int i, int j) {
    Member* temp = members[i];
    members[i] = members[j];
    members[j] = temp;
}

// sort the array according to last visited time and the average consumption
void sortMember(Member** members, int nMembers) {
    for (int i = 0; i < nMembers; i++) {
        for (int j = i; j > 0; j--) {
            if ((members[j]->getLastVisit() > members[j - 1]->getLastVisit()) || 
                (members[j]->getLastVisit() == members[j - 1]->getLastVisit() && members[j]->getAvgMonthlyExp() > members[j - 1]->getAvgMonthlyExp())) {
                swap(members, j, j - 1);
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
    excludeMember(members, n);
    sortMember(members, n);

    for (int i = 0; i < min(m, n); i++) 
        i != min(m, n)-1 ? cout << members[i]->getName() << "," : cout << members[i]->getName();

    for (int i = 0; i < n; i++) delete members[i];
    delete[] members;
}



