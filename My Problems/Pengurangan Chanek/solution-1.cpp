#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int arr[N];

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void rec(vector<long long> v, long long &ret) {
    if(v.size() == 1) {
        ret = max(ret, v[0]);
    } else {
        for(int i = 0 ; i < v.size() ; i++)
            for(int j = 0 ; j < v.size() ; j++) {
                if(i != j) {
                    vector<long long> temp = v;
                    temp.erase(temp.begin() + max(i, j));
                    temp.erase(temp.begin() + min(i, j));
                    temp.push_back(v[i] - v[j]);
                    rec(temp, ret);
                }
            }
    }
}

long long solve() {
    vector<long long> v;
    for(int i = 0 ; i < n ; i++) {
        v.push_back(arr[i]);
    }

    long long ret = -4e18;
    rec(v, ret);

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
