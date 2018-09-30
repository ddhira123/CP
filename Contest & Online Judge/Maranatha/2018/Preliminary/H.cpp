#include <bits/stdc++.h>
using namespace std;

int cnt[55];
int n; 
char dummy[55];

int main() {
  int t; cin >> t;

  for(int tc = 1 ; tc <= t ; tc++) {
    int n; scanf("%d", &n);
    memset(cnt, 0, sizeof cnt);

    for(int i = 0 ; i < n ; i++) {
      scanf("%s", dummy);
      int len = strlen(dummy);
      int depan = 9;

      if(len == 2) {
        if (dummy[0] == 'J') depan = 10;
        else if (dummy[0] == 'Q') depan = 11;
        else if (dummy[0] == 'K') depan = 12;
        else if (dummy[0] == 'A') depan = 0;
        else depan = dummy[0] - '0' - 1;
      }

      int belakang = 0;
      if (dummy[len-1] == 'H') belakang = 1;
      else if (dummy[len-1] == 'D') belakang = 2;
      else if (dummy[len-1] == 'C') belakang = 3;

      // printf("%s %d %d\n", dummy, depan, belakang);
      cnt[depan + belakang * 13]++; 
    }

    int drop = 0;
    int occ = 0;
    for(int i = 0 ; i < 52 ; i++) {
      if(cnt[i] > 0) {
        occ++;
        drop += cnt[i] - 1;
      }
    }

    if(occ == 52) {
      printf("FULLHOUSE %d\n", drop);
    } else {
      puts("INCOMPLETE");
    }
  }
  return 0;
}