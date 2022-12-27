#include<iostream>
using namespace std;
// The quenstion is longest-increasing-subsequence (LIS) problem
// Can be solved by dynamic programming
// https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/

int lis(int arr[], int n);

int _lis(int arr[], int n, int* maxRef);

int main() {
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << n - lis(arr, n) << endl;
    return 0;
}       

int _lis(int arr[], int n, int* maxRef) {
    //Base case 
    if (n == 1) return 1;
 
    // maxEndingHere is length of LIS
    // ending with arr[n-1]
    int res, maxEndingHere = 1;
 
    for (int i = 1; i < n; i++) {
        res = _lis(arr, i, maxRef);
        if (arr[i - 1] <= arr[n - 1]
            && res + 1 > maxEndingHere)
            maxEndingHere = res + 1;
    }
 
    // Compare max_ending_here with the overall
    // max. And update the overall max if needed
    if (*maxRef < maxEndingHere) *maxRef = maxEndingHere;
 
    // Return length of LIS ending with arr[n-1]
    return maxEndingHere;
}
 
// The wrapper function for _lis()
int lis(int arr[], int n) {
    // The max variable holds the result
    int max = 1;
 
    _lis(arr, n, &max);
 
    // returns max
    return max;
}