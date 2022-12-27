// author: R10521802

#include <iostream>
using namespace std;

const int M = 32768;

int myRand (int r, int a = 75, int c = 74, int m = M) {
    return (a * r + c) % m;
}

int normalize(float k) {
    float norm = -1 + 2 * (k / (M - 1));
    return static_cast<int>(norm*100);
}

int main() {
    int s, k;
    cin >> s >> k;
    int r = s;
    for (int i = 0; i < k; i++) {
        int x = myRand(r);
        r = x;
        int y = myRand(r);
        r = y;
        cout << normalize(x) << "," << normalize(y) << endl;
    }
}