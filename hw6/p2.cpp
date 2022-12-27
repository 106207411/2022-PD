#include<iostream>
using namespace std;

const int ZONES = 24;

int lackOfWorkers(int** worktypesArray, int** workloadArray, int** workersArray, int nWorkers, int nDays, int nTypes);

int main() {
    int nI, nJ, nK, L, w1, w2, R;
    cin >> nI >> nJ >> nK >> L >> w1 >> w2 >> R;
    int** kArray = new int*[nK+1];
    int** jArray = new int*[nJ];
    int** iArray = new int*[nI];
    for (int i = 0; i < nK+1; i++) {
        kArray[i] = new int[ZONES];
        for (int j = 0; j < ZONES; j++) cin >> kArray[i][j];
    }
    for (int i = 0; i < nJ; i++) {
        jArray[i] = new int[ZONES];
        for (int j = 0; j < ZONES; j++) cin >> jArray[i][j];
    }
    for (int i = 0; i < nI; i++) {
        iArray[i] = new int[nJ];
        for (int j = 0; j < nJ; j++) cin >> iArray[i][j];
    }

    cout << lackOfWorkers(kArray, jArray, iArray, nI, nJ, nK) << endl;

    delete[] kArray;
    delete[] jArray;
    delete[] iArray;
    return 0;
}       

int lackOfWorkers(int** worktypesArray, int** workloadArray, int** workersArray, int nWorkers, int nDays, int nTypes) {
    int lack = 0;
    for (int day = 0; day < nDays; day++) {
        int workersPerDay[ZONES] = {0};
        for (int nWorker = 0; nWorker < nWorkers; nWorker++) {
            int workType = workersArray[nWorker][day];
            int workTypeIdx = workType == 0 ? nTypes : workType - 1;
            for (int h = 0; h < ZONES; h++) {
                workersPerDay[h] += worktypesArray[workTypeIdx][h];
            }
        }
        for (int h = 0; h < ZONES; h++) {
            if (workersPerDay[h] < workloadArray[day][h]) {
                lack += workloadArray[day][h] - workersPerDay[h];
            }
        }
    }
    return lack;
}
