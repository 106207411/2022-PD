// author: R10521802

#include <iostream>
using namespace std;
int main() {
    // declare variables
    int nCrew = 0, thres = 0;
    cin >> nCrew >> thres;

    // declare the index of back, front and middle
    int idxBack = 0, idxFront = 0, idxMiddle = 0;

    // declare the current height of back, front and middle
    int hBack = 0, hFront = 0, hMiddle = 0;

    for (int i = 0; i < nCrew; i++) {
        int height = 0, pos = 0;
        cin >> height >> pos;

        // update the index only if the height is greater than the current height
        if (pos == 1) {
            if (height > hBack) {
                hBack = height;
                idxBack = i+1;
            }
        }
        if (pos == 2) {
            if (height > hFront) {
                hFront = height;
                idxFront = i+1; 
            }
        }
        if (pos == 3) {
            if (height > hMiddle) {
                hMiddle = height;
                idxMiddle = i+1;
            }
        }
    }
    cout << idxBack << "," << idxFront << "," << idxMiddle;
    return 0;
}