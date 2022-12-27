// author: R10521802

#include <iostream>
using namespace std;
int main() {
    // Declare variables
    int q = 0, s = 0, x = 0;
    // # of rows
    cin >> q;
    // iterate q times
    for (int i = 0; i < q; i++) {
        // Input
        cin >> s >> x;
        if (s == 0) 
            cout << x/12 << "," << x - 12 * (x/12) << endl;
        if (s == 1) 
            cout << x*12 << endl; 
    }
    
    return 0;
}