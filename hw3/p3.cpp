// author: R10521802

#include <iostream>
using namespace std;
int main() {
    int nDemand, nPrice, cost = 0;
    cin >> nDemand >> nPrice >> cost;
    int *candidatePrice = new int[nPrice];
    for (int i = 0; i < nPrice; i++) 
        cin >> candidatePrice[i];
        
    // 2D array 宣告: https://www.delftstack.com/zh-tw/howto/cpp/how-to-declare-2d-array-using-new-in-cpp/
    // probOfDemand[i][j] 代表單位零售價格為 candidatePrice[i]、需求量為 j 的機率
    int **probOfDemand = new int*[nPrice];
    for (int i = 0; i < nPrice; i++) {
        probOfDemand[i] = new int[nDemand+1];
        for (int j = 0; j < nDemand+1; j++) 
            cin >> probOfDemand[i][j];
    }

    int maxProfit = 0;
    int bestRetailPrice, nBestPurchase = 0;

    for (int i = 0; i < nPrice; i++) {
        // 單位零售價格
        int retailPrice = candidatePrice[i];

        // q 代表進貨量
        for (int q = 0; q <= nDemand; q++) {
            float profit = 0;
            for (int x = 0; x <= nDemand; x++) {
                int minXQ = x <= q ? x : q;
                profit += static_cast<float>(probOfDemand[i][x]) / 100 * minXQ;
            }
            profit = candidatePrice[i] * profit - cost * q;
            profit = static_cast<int>(profit * 100 + 0.5) / 100;
            
            if (profit > maxProfit) {
                maxProfit = profit;
                bestRetailPrice = retailPrice;
                nBestPurchase = q;
            }

            // 最大獲利相同時，先取相對較小的單位零售價格，再取較小的進貨量
            if (profit == maxProfit) {
                if (retailPrice < bestRetailPrice) {
                    bestRetailPrice = retailPrice;
                    nBestPurchase = q;
                }
                if (retailPrice == bestRetailPrice && q < nBestPurchase) 
                    nBestPurchase = q;
            }
        }
    }

    maxProfit = static_cast<int>(maxProfit * 100 + 0.5) / 100;
    cout << bestRetailPrice << "," << nBestPurchase << "," << maxProfit;
    return 0;
}