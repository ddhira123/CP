#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int n;

int dp1[N][10];
int dp2[N][4][10];

int getSuperb() {
  map<int, int> cnt;

  for (int i = 1 ; i <= n ; i++)
    cnt[arr[i]]++;

  int ans = n;
  for (auto it : cnt)
    ans = min(ans, n - it.second);
  return ans;
}

int solveGreat(int now, int lst) {
  if (now > n) return 0;
  int &ret = dp1[now][lst];

  if (ret != -1) return ret;
  ret = 1e9;

  for (int i = max(0, lst-1) ; i <= min(9, lst+1) ; i++) {
    ret = min(ret, solveGreat(now+1, i));
  }
  ret += (arr[now] != lst);

  return ret;
}

int getGreat() {
  memset(dp1, -1, sizeof dp1);
  int ret = 1e9;
  for (int i = 0 ; i <= 9 ; i++)
    ret = min(ret, solveGreat(1, i));
  return ret;
}

int solveGood(int now, int cnt, int lst) {
  if (now > n) {
    if (cnt < 3) return 1e9;
    return 0;
  }

  int &ret = dp2[now][cnt][lst];
  if (ret != -1) return ret;

  ret = 1e9;
  // new seq
  if (cnt >= 2) {
    for (int i = 0 ; i <= 9 ; i++) 
      ret = min(ret, solveGood(now+1, 0, i));
  }

  // continue seq
  for (int i = max(0, lst - 1); i <= min(9, lst + 1); i++) {
    ret = min(ret, solveGood(now + 1, min(3, cnt+1), i));
  }

  ret += (arr[now] != lst);
  return ret;
}

int getGood() {
  memset(dp2, -1, sizeof dp2);
  int ret = 1e9;

  for (int i = 0 ; i <= 9 ; i++)
    ret = min(ret, solveGood(1, 0, i));

  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1 ; i <= n ; i++)
    scanf("%d", &arr[i]);
  
  int a = getGood();
  int b = getGreat();
  int c = getSuperb();

  printf("%d %d %d\n", a, b, c);
  return 0;
}