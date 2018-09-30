#include <bits/stdc++.h>
using namespace std;

string s, t, r;

int main() {
  cin >> s >> t >> r;
  int n = s.length();

  vector<int> diffT, diffR;
  for(int i = 0 ; i < n ; i++) {
    if (s[i] != t[i]) diffT.push_back(i);
    if (s[i] != r[i]) diffR.push_back(i);
  }

  string ans = "";
  int tpos = -1, rpos = -1;

  for (int i = 0 ; i < n ; i++) {
    while (tpos + 1 < diffT.size() && diffT[tpos + 1] < i) tpos++;
    while (rpos + 1 < diffR.size() && diffR[rpos + 1] < i) rpos++;

    // cout << i << " " << tpos << " " << rpos << endl;
    if (tpos >= 1) goto hell;
    if (rpos >= 1) goto hell;

    for (int j = 'a' ; j <= 'z' ; j++)
      if ((s[i] != j) || (i == 0)) {
        int both = 0;
        int onlyT = 0;
        int onlyR = 0;

        if (j != t[i] && j != r[i]) both++;
        else if (j != t[i]) onlyT++;
        else if (j != r[i]) onlyR++;

        if (tpos == 0) {
          if (rpos == 0) {
            if (diffT[tpos] == diffR[rpos]) both++;
            else onlyT++, onlyR++;
          } else {
            onlyT++;
          }
        }

        if (rpos == 0 && tpos == -1) {
          onlyR++;
        }

        // cout << i << " " << j << " " << both << " " << onlyT << " " << onlyR << endl;

        int tpos2 = tpos+1;
        int rpos2 = rpos+1;

        if (tpos2 < diffT.size() && diffT[tpos2] == i) tpos2++;
        if (rpos2 < diffR.size() && diffR[rpos2] == i) rpos2++;

        if (tpos2 < diffT.size()) {
          if (diffT.size() - tpos2 == 1) {
            if (rpos2 < diffR.size()) {
              if (diffR.size() - rpos2 == 1) {
                if (diffR[rpos2] == diffT[tpos2]) both++;
                else onlyR++, onlyT++;
              } else {
                continue;
              }
            } else {
              onlyT++;
            }  
          } else {
            continue;
          }
        }

        if (rpos2 < diffR.size() && !(tpos2 < diffT.size() && diffT.size() - tpos2 == 1)) {
          if (diffR.size() - rpos2 == 1) {
            onlyR++;
          } else {
            continue;
          }
        }

        if (both + max(onlyR, onlyT) <= 1) {
          if (ans != "") {
            cout << "Ambiguous\n";
            return 0;
          } else {
            // cout << i << " " << j << endl;
            ans = s;
            ans[i] = j;
          }
        }
      }
  }

  hell:

  if (ans == "") ans = "Impossible";
  cout << ans << endl;
  return 0;
}