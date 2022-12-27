// author: R10521802

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LENGTH = 50;

struct Purchase {
    int itemID;
    int quantity;
};

class Member {
    private:
        int ID;
        int lastVisit;
        int avgMonthlyExp;
        int buyRecordCnt;
        char* name;
        Purchase* purchases;
    public:
        Member();
        Member(int ID, char* name, int lastVisit, int avgMonthlyExp, int purchaseCnt);
        ~Member();
        int getLastVisit();
        int getAvgMonthlyExp();
        char* getName();
        void makePurchase(int itemID, int quantity);
        int getPurchaseCnt(int itemID);
        void printLastPurchases(int n);
};

Member::Member() {
    ID = 0;
    lastVisit = 0;
    avgMonthlyExp = 0;
    buyRecordCnt = 0;
    name = nullptr;
    purchases = nullptr;
}

Member::Member(int ID, char* name, int lastVisit, int avgMonthlyExp, int totalRecordCnt) {
    this->ID = ID;
    this->lastVisit = lastVisit;
    this->avgMonthlyExp = avgMonthlyExp;
    this->name = new char[MAX_LENGTH+1];
    strcpy(this->name, name);
    purchases = new Purchase[totalRecordCnt];
    buyRecordCnt = 0;
}

Member::~Member() {
    delete [] name;
    delete [] purchases;
}

int Member::getLastVisit() { return lastVisit; }
int Member::getAvgMonthlyExp() { return avgMonthlyExp; }
char* Member:: getName() { return name; }

void Member::makePurchase(int itemID, int quantity) {
    purchases[buyRecordCnt].itemID = itemID;
    purchases[buyRecordCnt].quantity = quantity;
    buyRecordCnt++;
}

int Member::getPurchaseCnt(int itemID) {
    int cnt = 0;
    for (int i = 0; i < buyRecordCnt; i++) {
        if (purchases[i].itemID == itemID)
            cnt += purchases[i].quantity;
    }
    return cnt;
}

void Member::printLastPurchases(int n) {
    int start = buyRecordCnt - n;
    if (start < 0)
        start = 0;
    for (int i = start; i < buyRecordCnt; i++) {
        if (i == buyRecordCnt - 1)
            cout << purchases[i].itemID;
        else
            cout << purchases[i].itemID << ",";
    }
}

// exclude the member in the array 
// if not purchase d item or last visited time > 12
// update the number of remaining members
void excludeMember(Member** members, int& nMembers, int d) {
    int i = 0;
    while (i < nMembers) {
        if (members[i]->getLastVisit() > 12 || members[i]->getPurchaseCnt(d) == 0) {
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

// sort the array according to 
// purchase count of d item 
// last visited time and the average consumption
void sortMember(Member** members, int nMembers, int d) {
    for (int i = 0; i < nMembers; i++) {
        for (int j = i; j > 0; j--) {
            if ((members[j]->getPurchaseCnt(d) > members[j - 1]->getPurchaseCnt(d)) ||
                (members[j]->getPurchaseCnt(d) == members[j - 1]->getPurchaseCnt(d) && members[j]->getLastVisit() > members[j - 1]->getLastVisit()) || 
                (members[j]->getLastVisit() == members[j - 1]->getLastVisit() && members[j]->getAvgMonthlyExp() > members[j - 1]->getAvgMonthlyExp())) {
                swap(members, j, j - 1);
            }
            else break;
        }
    }    
}

void readInput(Member** members, int n, int p) {
    // read the member information (ID, name, last visited time, average monthly consumption)
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
        members[i] = new Member(i + 1, name, lastVisited[i], avgConsump[i], p);
        name = strtok(NULL, delim);
    }

    // read the purchase information (item ID, quantity)
    int* itemID = new int[p];
    int* quantity = new int[p];
    int* memberID = new int[p];
    for (int i = 0; i < p; i++) cin >> itemID[i];
    for (int i = 0; i < p; i++) cin >> quantity[i];
    for (int i = 0; i < p; i++) cin >> memberID[i];
    for (int i = 0; i < p; i++) {
        members[memberID[i] - 1]->makePurchase(itemID[i], quantity[i]);
    }
    
    delete[] nameData;
    delete[] lastVisited;
    delete[] avgConsump;
    delete[] itemID;
    delete[] quantity;
    delete[] memberID;
}

int main() {
    int n, m, p, r, d;
    cin >> n >> m >> p >> r >> d;
    Member** members = new Member*[n];
    readInput(members, n, p);
    excludeMember(members, n, d);
    sortMember(members, n, d);

    for (int i = 0; i < min(m, n); i++) {
        cout << members[i]->getName() << ",";
        members[i]->printLastPurchases(3);
        if (i != min(m, n) - 1)
            cout << endl;
    }

    for (int i = 0; i < n; i++) delete members[i];
    delete[] members;
}