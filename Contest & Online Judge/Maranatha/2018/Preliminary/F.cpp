#include <bits/stdc++.h>
using namespace std;

vector<string> parse(string s) {
  vector<string> ret;
  string str = "";

  for(char x : s) {
    if (x == '.') {
      ret.push_back(str);
      str = "";
    } else {
      str += x;
    }
  }

  return ret;
}

int main() {
  string dummy;
  getline(cin, dummy);
  
  vector<string> v = parse(dummy);
  if(v.size() == 1) {
    cout << v[0] << "\n";
    return 0;
  }

  map<string, int> cnt;
  for(int i = 1 ; i < v.size() ; i++) {
    set<string> s;
    string cur = v[i];
  
    for(int j = 0 ; j < cur.length() ; j++) {
      string val = "";
      for(int k = j ; k < cur.length() ; k++) {
        val += cur[k];
        
        s.insert(val);
      }
    }

    for(auto it : s)
      cnt[it]++;
  }

  string ans = "";
  {
    string cur = v[0];
    for(int j = 0 ; j < cur.length() ; j++) {
      string val = "";
      for(int k = j ; k < cur.length() ; k++) {
        val += cur[k];

        if(cnt[val] < v.size() - 1) {
          break;
        }

        if (val.length() > ans.length())
          ans = val;
      }
    }
  }

  cout << ans << endl;
  return 0;
}