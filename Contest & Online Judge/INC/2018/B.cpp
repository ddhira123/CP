#include <bits/stdc++.h>
using namespace std;

const int K = 400;
const int N = 1e5 + 5;

int arr[N];
vector<int> bucket[K];
int bucketPos[N];
int n, q;

void rebuildArrayFromBucket() {
  int it = 0;
  for (int i = 0 ; i < K ; i++) {
    for (int x : bucket[i]) {
      arr[it++] = x;
    }
    bucket[i].clear();
  }
}

void rebuildBucketFromArray() {
  for (int i = 0 ; i < n ; i++) {
    bucketPos[arr[i]] = i / K;
    bucket[i / K].push_back(arr[i]);
  }
}

int getIndex(int x) {
  int buck = bucketPos[x];
  int ret = 0;

  // printf("x %d buck %d\n", x, buck);
  for (int i = 0 ; i < buck ; i++)
    ret += bucket[i].size();
  
  // printf("%d\n", bucket[bu])
  for (int i = 0 ; i < bucket[buck].size() ; i++)
    if (bucket[buck][i] == x) {
      // printf("i %d bucket %d %d\n", i, buck, bucket[buck].size());
      return ret + i;
    }
  assert(-1);
  return -1;
}

int update(int a, int b) {
  int aa = getIndex(a);
  int bb = getIndex(b);

  int ret = bb+1 - aa;
  if (bb > aa)
    ret = bb-aa;
  
  // printf("yey %d\n", ret);
  // printf("a -> %d %d\n", a, aa);
  // printf("b -> %d %d\n", b, bb);

  int buckA = bucketPos[a];
  int buckB = bucketPos[b];

  bool ada = false;
  for (int i = 0 ; i < bucket[buckA].size() ; i++) {
    if (bucket[buckA][i] == a) {
      bucket[buckA].erase(bucket[buckA].begin()+i);
      ada = 1;
      break;
    }
  }
  assert(ada);

  bucketPos[a] = buckB;
  ada = false;
  for(int i = 0 ; i < bucket[buckB].size() ; i++) {
    if (bucket[buckB][i] == b) {
      bucket[buckB].insert(bucket[buckB].begin()+i+1, a);
      ada = true;
      break;
    }
  }
  // for (int x : bucket[buckB])
  //  printf("%d ", x);
  // puts("");
  assert(ada);

  return ret;
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 0 ; i < n ; i++) {
    // scanf("%d", &arr[i]);
    arr[i] = i+1;
  }
  rebuildBucketFromArray();

  for (int i = 1 ; i <= q ; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", update(a, b));

    if (i % K == 0) {
      rebuildArrayFromBucket();
      rebuildBucketFromArray();
    }
  }

  rebuildArrayFromBucket();
  for (int i = 0 ; i < n ; i++)
    printf("%d%c", arr[i], i+1==n ? '\n' : ' ');
  return 0;
}