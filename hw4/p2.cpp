// author: R10521802

#include <iostream>
using namespace std;

// return the worst iten id
int findWorst(int itemCount , int weightH , int weightS , const int revenue [], const int labor[], const int supply[], const int currentSol []);
// return whether to discard the worst item
bool shouldDiscardItem(int minC, int minP, int curC, int curP);

int main() {
    int itemCount, weightH, weightS = 0;
    int H, S = 0;
    cin >> itemCount >> weightH >> weightS >> H >> S;
    int *revenue = new int[itemCount];
    int *labor = new int[itemCount];
    int *supply = new int[itemCount];
    int *currentSol = new int[itemCount];

    for (int i = 0; i < itemCount; i++) cin >> revenue[i];
    for (int i = 0; i < itemCount; i++) cin >> labor[i];
    for (int i = 0; i < itemCount; i++) cin >> supply[i];
    for (int i = 0; i < itemCount; i++) currentSol[i] = 1;
    
    int currentH, currentS, currentR;
    do {
        currentH = 0;
        currentS = 0;
        currentR = 0;
        for (int i = 0; i < itemCount; i++) {
            currentH += labor[i] * currentSol[i];
            currentS += supply[i] * currentSol[i];
            currentR += revenue[i] * currentSol[i];
        }
        if (currentH > H || currentS > S) {
            int worstItem = findWorst(itemCount, weightH, weightS, revenue, labor, supply, currentSol);
            currentSol[worstItem] = 0;
        }
    } while (currentH > H || currentS > S);

    for (int i = 0; i < itemCount; i++) (i!=itemCount-1)? cout << currentSol[i] << "," : cout << currentSol[i] << ";" << currentR;
}


int findWorst(int itemCount , int weightH , int weightS , const int revenue [], const int labor[], const int supply[], const int currentSol []) {
    int minC = 2^30;
    int minP = 1;
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
    return (curC*minP < curP*minC || (curC*minP == curP*minC && curC < minC));
}