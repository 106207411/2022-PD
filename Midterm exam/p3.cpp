#include <iostream>
using namespace std;


int main() {
    int n = 0;
    cin >> n;
    int** timeArr = new int*[n];
    const int N = 4;
    for (int i = 0; i < n; i++) {
        timeArr[i] = new int[N];
        cin >> timeArr[i][0] >> timeArr[i][1] >> timeArr[i][2] >> timeArr[i][3];
    }

    int nOverlapped = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (timeArr[j][0]*60 + timeArr[j][1] < timeArr[i][2]*60 + timeArr[i][3] && 
                timeArr[i][0]*60 + timeArr[i][1] < timeArr[j][2]*60 + timeArr[j][3]) {
                nOverlapped++;
            }
        }
    }
    cout << nOverlapped;
    return 0;
}