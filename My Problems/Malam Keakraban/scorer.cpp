#include <bits/stdc++.h>
using namespace std;

void wa() {
    puts("WA");
    exit(0);    
}

vector<int> parse(int n, string s) {
    stringstream ss(s);
    vector<int> ret(n);

    for(int i = 0 ; i < n ; i++) {
        if(!(ss >> ret[i])) {
            wa();
        }
    }

    string temp;
    if(ss >> temp) {
        wa();
    }

    return ret;
}

vector<int> mapping(vector<int> v, vector<int> idxs) {
    vector<int> ret(v.size());
    for(int i = 0 ; i < ret.size() ; i++) {
        ret[i] = v[idxs[i] - 1];
    }
    return ret;
}

int calc(vector<int> v) {
    int ret = 0;

    for(int i = 0 ; i < v.size() ; i++) {
        ret += (v[i] == (v[(i+1) % v.size()]));
    }

    return ret;
}


int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ifstream out(argv[2]);
    ifstream con(argv[3]);
    string dummy;

    int tc;
    tc = 1;
   
    for(int t = 1 ; t <= tc ; t++) {
      int n;
      vector<int> arr;

      in >> n;
      for(int i = 0 ; i < n ; i++) {
        int x;
        in >> x;
        arr.push_back(x);
      }

      string judge;
      getline(out, judge);

      string contestant;
      if(!(getline(con, contestant))) {
        wa();
      }

      vector<int> judge_answer = parse(n, judge);
      vector<int> contestant_answer = parse(n, contestant);

      set<int> seen;
      for(int idx : contestant_answer) {
        if(idx < 1 || idx > n || seen.count(idx)) {
            wa();
        }
        seen.insert(idx);
      }

      vector<int> judge_mapping = mapping(arr, judge_answer);
      vector<int> contestant_mapping = mapping(arr, contestant_answer);

      if(calc(judge_mapping) < calc(contestant_mapping)) {
        wa();
      }
    }

    if(getline(con, dummy)) {
      wa();
    }

    puts("AC");
    return 0;
}