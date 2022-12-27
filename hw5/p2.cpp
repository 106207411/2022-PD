// author: R10521802

#include <iostream> 
#include <tuple>
using namespace std;

// return false if array is all 0
bool notEmpty(int arr[], int size);
// return the tuple of the two idx of toy and child with the highest preference
tuple<int, int> findMostPrefered(int T[], int C[], int P[10][20], int sizeT, int sizeC);
// return the final value of preference
int toyAssignment(int T[], int C[], int P[10][20], int n, int m);

int main() {
    int n, m;
    cin >> n >> m;
    int* toys = new int[n];
    int* children = new int[m];
    int preference[10][20] = {0};
    for (int i = 0; i < m; i++) {
        children[i] = 1;
        for (int j = 0; j < n; j++) {
            toys[j] = 1;
            cin >> preference[i][j];
        }
    }
    cout << toyAssignment(toys, children, preference, n, m);
    return 0;
}


bool notEmpty(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 1)
            return true;
    }
    return false;
}

tuple<int, int> findMostPrefered(int T[], int C[], int P[10][20], int sizeT, int sizeC) {
    int max = -1;
    int iStar, jStar;
    for (int i = 0; i < sizeC; i++) {
        for (int j = 0; j < sizeT; j++) {
            if (P[i][j] > max && C[i] == 1 && T[j] == 1 || 
                P[i][j] == max && C[i] == 1 && T[j] == 1 && j < jStar ||
                P[i][j] == max && C[i] == 1 && T[j] == 1 && j == jStar && i < iStar) {
                max = P[i][j];
                iStar = i;
                jStar = j;
            }
        }
    }
    return make_tuple(iStar, jStar);
}

int toyAssignment(int T[], int C[], int P[10][20], int n, int m) {
    int pSum = 0;
    int iStar, jStar;
    
    while (notEmpty(C, m)) {
        tie(iStar, jStar) = findMostPrefered(T, C, P, n, m);
        C[iStar] = 0;
        T[jStar] = 0;
        pSum += P[iStar][jStar];
    }
    return pSum;
}


