// author: R10521802

#include <iostream>
using namespace std;
int main() {
    int nCrew = 0, thres = 0;
    cin >> nCrew >> thres;
    int nBack = 0, nFront = 0, nMiddle = 0;
    for (int i = 0; i < nCrew; i++) {
        int height = 0, pos = 0;
        cin >> height >> pos;
        if (height >= thres*12) {
            if (pos == 1) nBack++;
            if (pos == 2) nFront++;
            if (pos == 3) nMiddle++;
        }
    }
    cout << nBack << "," << nFront << "," << nMiddle;
    return 0;
}