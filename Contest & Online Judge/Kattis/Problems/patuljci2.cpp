#include <bits/stdc++.h>
using namespace std;

const int N = 300005; 
const int MAX_NODE = 300005 * 20;

struct Node {
  int cnt;
  int L, R;

  Node() {
    cnt = 0;
    L = -1;
    R = -1;
  }
};

int node_count;
int roots[N];
Node nodes[MAX_NODE];
int n, c;
int arr[N];

void init(int id, int l, int r) {
  if(l < r) {
    int m = (l + r) / 2;

    nodes[id].L = node_count++;
    nodes[id].R = node_count++;

    init(nodes[id].L, l, m);
    init(nodes[id].R, m+1, r);
  }
}

void build(int prv_id, int id, int l, int r, int x) {
  nodes[id].cnt = nodes[prv_id].cnt + 1;

  if(l < r) {
    int m = (l + r) / 2;

    if(x <= m) {
      nodes[id].L = node_count++;
      nodes[id].R = nodes[prv_id].R;

      build(nodes[prv_id].L, nodes[id].L, l, m, x);
    } else {
      nodes[id].L = nodes[prv_id].L;
      nodes[id].R = node_count++;

      build(nodes[prv_id].R, nodes[id].R, m+1, r, x);
    }
  }
}

int query(int lver, int rver) {
  int thres = (rver - lver + 1) / 2;
  lver--;

  lver = roots[lver];
  rver = roots[rver];

  int l = 1, r = c;

  while(l < r) {
    int m = (l + r) / 2;
    if(nodes[nodes[rver].L].cnt - nodes[nodes[lver].L].cnt > thres) {
      r = m;
      rver = nodes[rver].L;
      lver = nodes[lver].L;
    } else if (nodes[nodes[rver].R].cnt - nodes[nodes[lver].R].cnt > thres) {
      l = m+1;
      rver = nodes[rver].R;
      lver = nodes[lver].R;
    } else {
      return -1;
    }
  }

  return l;
}

void read() {
  scanf("%d %d", &n, &c);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  roots[0] = node_count++;
  init(roots[0], 1, c);

  for(int i = 1 ; i <= n ; i++) {
    roots[i] = node_count++;
    build(roots[i-1], roots[i], 1, c, arr[i]);
  }
}

void work() {
  int q; scanf("%d", &q);

  for(int i = 0 ; i < q ; i++) {
    int l, r;
    scanf("%d %d", &l, &r);

    int ret = query(l, r);
    if(ret == -1) {
      puts("no");
    } else {
      printf("yes %d\n", ret);
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}