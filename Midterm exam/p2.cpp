#include <iostream>
using namespace std;


int main() {
    int n = 0, k = 0;
    cin >> n >> k;
    int nOfnegative = 0;
    int position = 0;
    int negValue = 0;
    for (int i = 0; i < n; i++) {
        int value = 0;
        cin >> value;
        if (value < 0) {
            nOfnegative ++;
            position = i + 1;
            negValue = value;
        }
        if (nOfnegative == k || (nOfnegative > 0 && i == n - 1)) {
            cout << position << "," << negValue;
            break;
        }
        if (nOfnegative == 0 && i == n - 1) {
            cout << 0;
        }
    }
    return 0;
}