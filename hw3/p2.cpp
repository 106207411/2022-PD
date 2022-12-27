// author: R10521802

#include <iostream>
using namespace std;
int main() {
    int nDemand = 0, retailPrice = 0, cost = 0;
    cin >> nDemand >> retailPrice >> cost;
    int *probOfDemand = new int[nDemand+1];
    for (int i = 0; i <= nDemand; i++) 
        cin >> probOfDemand[i];

    float maxProfit = 0, nBestPurchase = 0;

    // q 代表進貨量
    for (int q = 0; q <= nDemand; q++) {
        float profit = 0;

        for (int x = 0; x <= nDemand; x++) 
            profit += static_cast<float>(probOfDemand[x]) / 100 * min(x, q);
        profit = retailPrice * profit - cost * q;

        if (profit > maxProfit) {
            maxProfit = profit;
            nBestPurchase = q;
        }
    }
    maxProfit = static_cast<int>(maxProfit * 100 + 0.5) / 100;
    cout << nBestPurchase << "," << maxProfit;

    return 0;
}