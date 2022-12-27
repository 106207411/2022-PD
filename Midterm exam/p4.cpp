#include <iostream>
using namespace std;


int main() {
    int n = 0, k = 0, l = 0;
    cin >> n >> k >> l;
    int** cityDist = new int*[n];
    for (int i = 0; i < n; i++) {
        cityDist[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> cityDist[i][j];
        }
    }

    int* cityWithHospital = new int[k];
    for (int i = 0; i < k; i++) {
        cin >> cityWithHospital[i];
    }

    int sumDistToHospital = 0;
    int nHappyCity = 0;
    for (int i = 0; i < n; i++) {
        int minDist = 1000000;
        for (int j = 0; j < k; j++) {
            if (cityDist[i][cityWithHospital[j]-1] < minDist) {
                minDist = cityDist[i][cityWithHospital[j]-1];
            }
        }
        sumDistToHospital += minDist;
        if (minDist <= l) {
            nHappyCity++;
        }
    }
    cout << sumDistToHospital << "," << nHappyCity;
    return 0;
}