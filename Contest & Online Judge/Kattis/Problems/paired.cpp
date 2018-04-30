#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

map<int, long long> mapping;
set<long long> used_mapping;

long long get_rand() {
  return rand() | ((1ll * rand()) << 32);
}

long long get_mapping(int x) {
  if(mapping.count(x)) {
    return mapping[x];
  }

  long long ret = get_rand();
  while(used_mapping.count(ret)) {
    ret = get_rand();
  }

  mapping[x] = ret;
  used_mapping.insert(ret);

  return ret;
}

int arr[N];
long long pxor[N];
int n;

map<long long, int> compressed;
queue<int> q[N];
int cnt[N];

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  set<long long> seen;
  for(int i = 1 ; i <= n ; i++) {
    pxor[i] = get_mapping(arr[i]) ^ pxor[i-1];
    seen.insert(pxor[i]);
  }
  seen.insert(0);

  int idx = 0;
  for(long long it : seen) {
    compressed[it] = idx++; 
  }
}

int work() {
  int ret = 0;
  int l = 1;
  q[compressed[0]].push(0);

  for(int r = 1 ; r <= n ; r++) {
    cnt[arr[r]]++;

    while(cnt[arr[r]] == 3) {
      cnt[arr[l]]--;
      q[compressed[pxor[l-1]]].pop();

      l++;
    }

    int cur = compressed[pxor[r]];
    if(!q[cur].empty()) {
      ret = max(ret, r - q[cur].front());
    }

    q[cur].push(r);
  }

  return ret;
}

int main() {
  srand(time(NULL));
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}