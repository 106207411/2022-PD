// author: R10521802

#include <iostream>
using namespace std;

struct Order {
    int ID;
    int revenue;
    int labor;
    int supply;
};

// return whether to discard the worst item
bool shouldDiscardItem(int minC, int minP, int curC, int curP) {
    return (curC*minP < curP*minC || (curC*minP == curP*minC && curC < minC));
}

// return the worst iten id
int findWorst(int itemCount , int weightH , int weightS , const Order orders[], const int currentSol []) {
    int minC = 2^30;
    int minP = 1;
    int badItemId = 0;
    for (int i = 0; i < itemCount; i++) {
        if (currentSol[i] == 1) {
            int curC = orders[i].revenue;
            int curP = weightH*orders[i].labor + weightS*orders[i].supply;
            if (shouldDiscardItem(minC, minP, curC, curP)) {
                badItemId = i;
                minC = curC;
                minP = curP;
            }
        }
    }
    return badItemId;
}


int main() {
    int itemCount, weightH, weightS = 0;
    int H, S = 0;
    cin >> itemCount >> weightH >> weightS >> H >> S;
    Order *orders = new Order[itemCount];
    int *currentSol = new int[itemCount];

    for (int i = 0; i < itemCount; i++) {
        orders[i].ID = i+1;
        cin >> orders[i].revenue;
    }
    for (int i = 0; i < itemCount; i++) cin >> orders[i].labor;
    for (int i = 0; i < itemCount; i++) cin >> orders[i].supply;
    for (int i = 0; i < itemCount; i++) currentSol[i] = 1;
    
    int currentH, currentS, currentR;
    do {
        currentH = 0;
        currentS = 0;
        currentR = 0;
        for (int i = 0; i < itemCount; i++) {
            currentH += orders[i].labor * currentSol[i];
            currentS += orders[i].supply * currentSol[i];
            currentR += orders[i].revenue * currentSol[i];
        }
        if (currentH > H || currentS > S) {
            int worstItem = findWorst(itemCount, weightH, weightS, orders, currentSol);
            currentSol[worstItem] = 0;
        }
    } while (currentH > H || currentS > S);

    for (int i = 0; i < itemCount; i++) (i!=itemCount-1)? cout << currentSol[i] << "," : cout << currentSol[i] << ";" << currentR;
}