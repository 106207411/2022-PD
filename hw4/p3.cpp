// author: R10521802

#include <iostream>
using namespace std;

// return the worst iten id
int findWorst(int itemCount, int weightH, int weightS, int currentSol [], const int revenue [], const int labor[], const int supply[]);
// return whether to discard the worst item
bool shouldDiscardItem(int minC, int minP, int curC, int curP);
// return whether to update the optimal weight H and S
bool shouldUpdateWeights(int currentR, int optRevenue, int weightH, int optWeightH, int weightS, int optWeightS);
// return the optimal revenue
int findOptOrders(int itemCount, int weightH , int weightS, const int H, const int S, const int revenue [], const int labor[], const int supply[]);

int main() {
    const int weightHMax = 5, weightSMax = 5;
    int itemCount = 0, H = 0, S = 0;
    cin >> itemCount >> H >> S;
    int *revenue = new int[itemCount];
    int *labor = new int[itemCount];
    int *supply = new int[itemCount];
    int optWeightH, optWeightS, optRevenue = 0;

    for (int i = 0; i < itemCount; i++) cin >> revenue[i];
    for (int i = 0; i < itemCount; i++) cin >> labor[i];
    for (int i = 0; i < itemCount; i++) cin >> supply[i];
    
    for (int weightS = 0; weightS <= weightSMax; weightS++) {
        for (int weightH = 0; weightH <= weightHMax; weightH++) {
            if (weightH + weightS == 0) continue;
            int currentR = findOptOrders(itemCount, weightH, weightS, H, S, revenue, labor, supply);
            if (shouldUpdateWeights(currentR, optRevenue, weightH, optWeightH, weightS, optWeightS)) {
                optRevenue = currentR;
                optWeightH = weightH;
                optWeightS = weightS;
            }
        }
    }
    cout << optWeightH << "," << optWeightS << "," << optRevenue << endl;
}

int findWorst(int itemCount, int weightH, int weightS, int currentSol [], const int revenue [], const int labor[], const int supply[]) {
    int minC = 0;
    int minP = 0;
    int badItemId = 0;
    for (int i = 0; i < itemCount; i++) {
        if (currentSol[i] == 1) {
            int curC = revenue[i];
            int curP = weightH*labor[i] + weightS*supply[i];
            if (shouldDiscardItem(minC, minP, curC, curP)) {
                badItemId = i;
                minC = curC;
                minP = curP;
            }
        }
    }
    return badItemId;
}

bool shouldDiscardItem(int minC, int minP, int curC, int curP) {
    if (minP == 0 && minC == 0) return true;
    return (curC*minP < curP*minC || (curC*minP == curP*minC && curC < minC));
}

bool shouldUpdateWeights(int currentR, int optRevenue, int weightH, int optWeightH, int weightS, int optWeightS) {
    return (currentR > optRevenue || (currentR == optRevenue && weightH < optWeightH) || (currentR == optRevenue && weightH == optWeightH && weightS < optWeightS));
}

int findOptOrders(int itemCount, int weightH , int weightS, const int H, const int S, const int revenue [], const int labor[], const int supply[]) {
    int currentH = 0, currentS = 0, currentR = 0;
    int *currentSol = new int[itemCount];

    for (int i = 0; i < itemCount; i++) {
        currentSol[i] = 1;
        currentH += labor[i];
        currentS += supply[i];
        currentR += revenue[i];
    }
    
    while (currentH > H || currentS > S) {
        int badItemId = findWorst(itemCount, weightH, weightS, currentSol, revenue, labor, supply);
        currentH -= labor[badItemId];
        currentS -= supply[badItemId];
        currentR -= revenue[badItemId];
        currentSol[badItemId] = 0;
    }
    
    return currentR;
}