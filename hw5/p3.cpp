// author: R10521802

#include <iostream>
using namespace std;

// exclude the element in the array if last visited time > 12
// return the number of elements left in the array
int excludeMember(int lastVisited[], int avgConsump[], int memberId[], int len);

// sort the array according to last visited time and the average consumption
void sortMember(int lastVisited[], int avgConsump[], int memberId[], int len);

// swap the two elements in the array
void swap(int array[], int i, int j);


int main() {
    int n, m;
    cin >> n >> m;
    int* lastVisited = new int[n];
    int* avgConsump = new int[n];
    int* memberId = new int[n];
    for (int i = 0; i < n; i++) cin >> lastVisited[i];
    for (int i = 0; i < n; i++) cin >> avgConsump[i];
    for (int i = 0; i < n; i++) memberId[i] = i + 1;

    // It confuses me to get the size of dynamically allocated array, so I just note it here
    // https://stackoverflow.com/questions/2950332/why-does-a-c-array-have-a-wrong-sizeof-value-when-its-passed-to-a-function
    // - 'sizeof(point)/sizeof(point[0])' trick doesn't work for a dynamically allocated array, only an array allocated on the stack

    // Bad code, but it returns size of array which is what I want
    int nOfMember = excludeMember(lastVisited, avgConsump, memberId, n);
    sortMember(lastVisited, avgConsump, memberId, nOfMember);

    for (int i = 0; i < min(m, nOfMember); i++) 
        i != min(m, nOfMember)-1 ? cout << memberId[i] << "," : cout << memberId[i];
}

int excludeMember(int lastVisited[], int avgConsump[], int memberId[], int len) {
    int i = 0;
    while (i < len) {
        if (lastVisited[i] > 12) {
            for (int j = i; j < len - 1; j++) {
                lastVisited[j] = lastVisited[j + 1];
                avgConsump[j] = avgConsump[j + 1];
                memberId[j] = memberId[j + 1];
            }
            len--;
        }
        else i++;
    }
    return len;
}

void sortMember(int lastVisited[], int avgConsump[], int memberId[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i; j > 0; j--) {
            if ((lastVisited[j] > lastVisited[j - 1]) || 
                (lastVisited[j] == lastVisited[j - 1] && avgConsump[j] > avgConsump[j - 1]) ||
                (lastVisited[j] == lastVisited[j - 1] && avgConsump[j] == avgConsump[j - 1] && memberId[j] < memberId[j - 1])) {
                swap(lastVisited, j, j - 1);
                swap(avgConsump, j, j - 1);
                swap(memberId, j, j - 1);
            }
            else break;
        }
    }    
}

void swap(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}