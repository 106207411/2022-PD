// author: R10521802

#include <iostream>
using namespace std;
int main() {
    int nCrew = 0, thres = 0, total = 0;
    cin >> nCrew >> thres;
    for (int i = 0; i < nCrew; i++) {
        int height = 0;
        cin >> height;
        if (height >= thres*12) total++;
    }
    cout << total;
    return 0;
}