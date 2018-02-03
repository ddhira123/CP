#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int dp[3][N];
int arr[3][N];
int n;

void read() {
    cin >> n;
    for(int i = 1 ; i <= 2 ; i++)
        for(int j = 1 ; j <= n ; j++) {
            cin >> arr[i][j];
        }
}

int work() {
    for(int i = 1 ; i <= 2 ; i++)
        for(int j = 1 ; j <= n ; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + arr[i][j];
        }

    return dp[2][n];
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}