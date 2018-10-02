#include <bits/stdc++.h>
using namespace std;

const int S = 5001;

int dp[S][S];
int n, k, s;
int arr[S];

void read() {
  scanf("%d %d %d", &n, &k, &s);
  for(int i = 0 ; i < n ; i++) {
    scanf("%d", &arr[i]);
  }
}

int DP() {
  dp[k][0] = 0;
  for(int i = 1 ; i <= s ; i++)
    dp[k][i] = 1e9;
  
  for(int i = k-1 ; i >= 0 ; i--) {
    vector<int> points;
    
    for(int j = i ; j < n ; j += k)
      points.push_back(arr[j]);
    sort(points.begin(), points.end());

    int mins = dp[i+1][0];

    for(int sum = 0 ; sum <= s ; sum++) {
      mins = min(mins, dp[i+1][sum]);
      dp[i][sum] = mins + points.size();

      for(int j = 0 ; j < points.size() ; ) {
        int it = j;
        while(it < points.size() && points[it] == points[j])
          it++;
        
        if (points[j] <= sum) {
          int change = points.size() - (it - j); 
          dp[i][sum] = min(dp[i][sum], dp[i + 1][sum - points[j]] + change);
        } else {
          break;
        }

        j = it;
      }
    }
  }

  return dp[0][s];
}

int main() {
  read();
  printf("%d\n", DP());
  return 0;
}