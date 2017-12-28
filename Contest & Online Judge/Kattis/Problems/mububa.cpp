#include <bits/stdc++.h>
using namespace std;

const int N = 3005;

int dp[N][N];
long long sum[N];
int n;

long long getSum(int l,int r) {
    return sum[r] - sum[l-1];
}

void read() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
}

int DP() {
    for(int i = n ; i >= 1 ; i--) {
        int ptr = i;

        for(int j = i ; j < n ; j++) {
            ptr = max(ptr,j + 1);
            while(ptr <= n && getSum(i,j) > getSum(j+1,ptr)) ptr++;
            if(ptr > n) 
                dp[i][j] = -N;
            else
                dp[i][j] = 1 + dp[j+1][ptr];
        }

        dp[i][n] = 1;
        for(int j = n-1 ; j >= i ; j--)
            dp[i][j] = max(dp[i][j],dp[i][j+1]);
    }

    return dp[1][1];
}

int main() {
    read();
    cout << DP() << "\n";
    return 0;
} 

