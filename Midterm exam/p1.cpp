#include <iostream>
using namespace std;


int main() {
    int n = 0;
    cin >> n;
    int nOfnegative = 0;
    for (int i = 0; i < n; i++) {
        int value = 0;
        cin >> value;
        if (value < 0) {
            nOfnegative ++;
            if (nOfnegative == 2) {
               cout << i + 1;
               break;
            }
        }
    }
    return 0;
}