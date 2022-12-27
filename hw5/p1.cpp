// author: R10521802

#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    long long int combination = 1;
    for (int i = 1; i <= m; i++) {
        combination *= (n - i + 1);
        combination /= i;
    }
    cout << combination << endl;
}
