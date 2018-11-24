#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int arr[N];
int n;

void read() {
  cin >> n;
  for (int i = 1 ; i <= n ; i++)
    cin >> arr[i];
}

bool test(int k) {
  for (int i = 1 ; i <= k ; i++) {
    int val = arr[i] - arr[i-1];
    for (int j = i ; j <= n ; j += k) {
      if (val != arr[j] - arr[j-1])
        return false;
    }
  }
  return true;
}

void work() {
  vector<int> ret;
  for (int i = 1 ; i <= n ; i++)
    if (test(i)) {
      ret.push_back(i);
    }
  cout << ret.size() << endl;
  for (int x : ret) printf("%d ", x);
  puts("");
}

int main() {
  read();
  work();
  return 0;
}