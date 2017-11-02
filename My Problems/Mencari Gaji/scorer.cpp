#include <bits/stdc++.h>

using namespace std;

void wa() {
    puts("WA");
    exit(0);
}

ifstream testcase_input, judges_output, contestant_output;

int n, m, k, s, p;
int u[100005], v[100005], x[100005];

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

bool in_range(vector<int> v, int lo, int hi) {
    for(int x : v) {
        if(x < lo || x > hi) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv) {
    // prepare the input for official testcase files
    testcase_input.open(argv[1]);
    judges_output.open(argv[2]);
    contestant_output.open(argv[3]);

    testcase_input >> n >> m >> k >> s;
    s--;
    for (int i = 0; i < m; i++) {
        testcase_input >> u[i] >> v[i];
        u[i]--;
        v[i]--;
    }

    for (int i = 0; i < k; i++) {
        testcase_input >> x[i];
        x[i]--;
    }

    testcase_input >> p;

    string dummy;

    getline(judges_output, dummy);
    vector<int> judge_ans = parse(n, dummy);

    if(!getline(contestant_output, dummy)) {
        wa();
    }

    vector<int> contestant_ans = parse(n, dummy);

    if(getline(contestant_output, dummy)) {
        wa();
    }

    if(!in_range(contestant_ans, 1, n)) {
        wa();
    }

    for (int i = 0; i < m; i++) {
        if (contestant_ans[u[i]] >= contestant_ans[v[i]])
            wa();
    }

    for (int i = 0; i < k; i++) {
        if (contestant_ans[x[i]] == contestant_ans[s])
            wa();
    }

    if(p == 2 && judge_ans < contestant_ans) {
        wa();
    }

    puts("AC");
    return 0;
}
