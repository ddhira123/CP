#include <bits/stdc++.h>
using namespace std;

void wa() {
    puts("WA");
    exit(0);    
}

bool in_range(int low, int x ,int hi) {
    return low <= x && x <= hi;
}

vector<int> parse_contestant(int n, string s) {
    stringstream ss(s);
    vector<int> ret(n);

    for(int i = 0 ; i < n ; i++) {
        if(!(ss >> ret[i])) {
            wa();
        }
    }

    int temp;
    if(ss >> temp) {
        wa();
    }

    return ret;
}

vector<int> parse_judge(string s) {
    stringstream ss(s);
    vector<int> ret;
    int dummy;

    while(ss >> dummy) {
        ret.push_back(dummy);
    }

    return ret;
}

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ifstream out(argv[2]);
    ifstream con(argv[3]);
    string dummy;

    int tc; in >> tc;
    vector<int> N(tc), M(tc), K(tc);

    for(int t = 0 ; t < tc ; t++) {
        in >> N[t] >> M[t] >> K[t];
    }

    // get judge's output
    vector<vector<int>> judge;

    while(getline(out, dummy)) {
        judge.push_back(parse_judge(dummy));
    }

    // get contestant's output
    vector<vector<int>> contestant;

    while(judge.size() > contestant.size() && getline(con, dummy)) {
        int n = N[contestant.size()];
        contestant.push_back(parse_contestant(n, dummy));
    }

    if(getline(con, dummy) || judge.size() != contestant.size()) {
        wa();
    }

    // check valid answer
    for(int t = 0 ; t < tc ; t++) {
        int n = N[t];
        int m = M[t];
        int k = K[t];

        // check valid output
        if(contestant[t][0] == -1) {
            for(int x : contestant[t]) 
                if(x != -1)
                    wa();
        } else {
            for(int x : contestant[t])
                if(!in_range(1, x, m))
                    wa();
        }

        // contestant found answer but judge doesnt
        if(contestant[t][0] != -1 && judge[t][0] == -1) {
            wa();
        }
        // contestant doesnt found answer but judge does
        if(contestant[t][0] == -1 && judge[t][0] != -1) {
            wa();
        }

        // if answer exists, check its validity
        if(contestant[t][0] != -1) {
            map<int, int> cnt;
            int l = 0;

            for(int r = 0 ; r < n ; r++) {
                int val = contestant[t][r];
                cnt[val]++;

                while(cnt[val] == 2) {
                    cnt[contestant[t][l]]--;
                    l++;
                }

                k = max(-1, k - (r-l+1));
            }

            if(k != 0) {
                wa();
            }
        }
    }

    puts("AC");
    return 0;
}