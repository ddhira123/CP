#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int cnt[N];
int SA[N], tmpS[N];
int RA[N], tmpR[N];
int phi[N], PLCP[N], LCP[N];

char s[N];
int len;

void radixSort(int k) {
  int maxx = max(len, 300);
  for (int i = 0; i < maxx; i++) cnt[i] = 0;
  for (int i = 0; i < len; i++) cnt[i + k < len ? RA[i + k] : 0]++;

  int tot = 0;
  for (int i = 0; i < maxx; i++) {
    int tmp = cnt[i];
    cnt[i] = tot;
    tot += tmp;
  }

  for (int i = 0; i < len; i++)
    tmpS[cnt[SA[i] + k < len ? RA[SA[i] + k] : 0]++] = SA[i];
  for (int i = 0; i < len; i++) SA[i] = tmpS[i];
}

void buildSA() {
  for (int i = 0; i < len; i++) {
    SA[i] = i;
    RA[i] = s[i];
  }
  for (int lg = 1; lg < len; lg <<= 1) {
    radixSort(lg);
    radixSort(0);
    int tot = 0;
    tmpR[SA[0]] = 0;
    for (int i = 1; i < len; i++)
      tmpR[SA[i]] =
          (RA[SA[i]] == RA[SA[i - 1]] && SA[i] + lg < len &&
           SA[i - 1] + lg < len && RA[SA[i] + lg] == RA[SA[i - 1] + lg])
              ? tot
              : ++tot;

    for (int i = 0; i < len; i++) RA[i] = tmpR[i];
    if (RA[SA[len - 1]] == len - 1) break;
  }
}

void buildLCP() {
  phi[SA[0]] = -1;
  for (int i = 1; i < len; i++) phi[SA[i]] = SA[i - 1];
  for (int i = 0, l = 0; i < len; i++) {
    if (phi[i] == -1)
      PLCP[i] = 0;
    else {
      while (s[i + l] == s[phi[i] + l]) l++;
      PLCP[i] = l;
      l = max(0, l - 1);
    }
  }
  for (int i = 0; i < len; i++) LCP[i] = PLCP[SA[i]];
}

int main() {
  scanf("%s", s);
  len = strlen(s);
  s[len++] = '$';
  s[len] = '\0';
  buildSA();
  buildLCP();

  int mx = 0;
  int st = -1;

  for (int i = len-1 ; i >= 1 ; i--) {
    if (LCP[i] >= mx) {
      mx = LCP[i];
      st = SA[i];
    }
  }

  for (int i = 0 ; i < mx ; i++) {
    printf("%c", s[st + i]);
  }
  puts("");
  
  return 0;
}
