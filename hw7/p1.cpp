// author: R10521802

#include <iostream>
#include <vector>
using namespace std;

const int ZONES = 24;

void readInput(int** shifts, int** demands, int nK, int nJ) {
    // read shifts
    for (int i = 1; i <= nK; i++) {
        shifts[i] = new int[ZONES];
        for (int j = 0; j < ZONES; j++) {
            cin >> shifts[i][j];
        }
    }
    shifts[0] = new int[ZONES];
    for (int j = 0; j < ZONES; j++) {
        cin >> shifts[0][j];
    }
    // read demands
    for (int i = 0; i < nJ; i++) {
        demands[i] = new int[ZONES];
        for (int j = 0; j < ZONES; j++) {
            cin >> demands[i][j];
        }
    }
}

void arrangeWorkSchedule(int **workload, int nJ, int nI, int nK, int L) {
    int **sevenDayworks = new int*[7];
    vector<int> goodDayworks;

    // intialize sevenDayworks 
    for (int i = 0; i < 7; i++) {
        int conscutiveDayoff = 0;
        int dayoffs = 0;
        sevenDayworks[i] = new int[nJ];
        for (int j = 0; j < nJ; j++) {
            // 1 means daywork, 0 means dayoff
            if (i == 6 && j == 0) {
                sevenDayworks[i][j] = 0;
                dayoffs++;
            }
            else
                sevenDayworks[i][j] = 1;
        }

        for (int j = i; j < nJ; j++) {
            if (conscutiveDayoff < 2) {
                sevenDayworks[i][j] = 0;
                conscutiveDayoff++;
                dayoffs++;
            }
            else {
                conscutiveDayoff = 0;
                j += 4;
            }
        }
        if (dayoffs == L) goodDayworks.push_back(i);
    }

    // arrange workload
    for (int i = 0; i < nI; i++) {
        workload[i] = new int[nJ];
        int *workArr = sevenDayworks[goodDayworks[i%goodDayworks.size()]];
        for (int j = 0; j < nJ; j++)
            workload[i][j] = workArr[j];
    }

    int nAssigned = 0;
    for (int j = 0; j < nJ; j++) {
        for (int i = 0; i < nI; i++) {
            if (workload[i][j] != 0) {
                workload[i][j] = nAssigned % nK + 1;
                nAssigned++;
            }
        }
    }

    // release memory
    for (int i = 0; i < 7; i++) {
        delete[] sevenDayworks[i];
    }
    delete[] sevenDayworks;
}

int lackOfWorkers(int nI, int nJ, int nK, int L, int w1, int w2, int R) {
    int **shifts = new int*[nK+1];
    int **demands = new int*[nJ];
    int **workload = new int*[nI];

    readInput(shifts, demands, nK, nJ);
    arrangeWorkSchedule(workload, nJ, nI, nK, L);

    // calculate the lack of workers
    int lack = 0;
    for (int day = 0; day < nJ; day++) {
        int workersPerDay[ZONES] = {0};
        for (int worker = 0; worker < nI; worker++) {
            for (int h = 0; h < ZONES; h++) 
                workersPerDay[h] += shifts[workload[worker][day]][h];
        }
        for (int h = 0; h < ZONES; h++) 
            lack += max(0, demands[day][h] - workersPerDay[h]);
    }

    return lack;
}

int main() {
    int nI, nJ, nK, L, w1, w2, R;
    cin >> nI >> nJ >> nK >> L >> w1 >> w2 >> R;
    cout << lackOfWorkers(nI, nJ, nK, L, w1, w2, R);
    return 0;
}