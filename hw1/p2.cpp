// author: R10521802

#include <iostream>
using namespace std;
int main() {
    // Declare variables
    int s = 0, x = 0;
    // Input
    cin >> s >> x;
    
    if (s == 0) 
        cout << x/12 << "," << x - 12 * (x/12);
    if (s == 1) 
        cout << x*12; 
    
    return 0;
}