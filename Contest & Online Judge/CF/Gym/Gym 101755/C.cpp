#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int INF = 1e9;

int n;
pair<int, int> arr[N];

void read() {
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++) {
    scanf("%d %d", &arr[i].first, &arr[i].second);
  }
}

void solve() {
  sort(arr, arr + n);
  int mins = INF;

  vector<int> ans;
  for(int i = 0 ; i < n ; i++) {
    if (mins < arr[i].first) {
      ans.push_back(mins);
      mins = arr[i].second;
    } else {
      mins = min(mins, arr[i].second);
    }
  }

  ans.push_back(mins);
  cout << ans.size() << endl;
  for(int x : ans) printf("%d ", x);
  puts("");
}

int main() {
  read();
  solve();
  return 0;
}