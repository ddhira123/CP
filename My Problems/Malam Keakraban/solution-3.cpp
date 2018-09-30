#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int arr[N];
vector<int> indices[N];

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

void solve() {
    for(int i = 1 ; i <= n ; i++) {
        indices[arr[i]].push_back(i);
    }

    int mx = 1;
    for(int i = 2 ; i <= n ; i++) {
        if(indices[mx].size() < indices[i].size()) {
            mx = i;
        }
    }

    vector<pair<int,int>> v;

    for(int i = 1 ; i <= n ; i++) {
        if(i == mx) {
            v.push_back({indices[i].size(), i});
        } else if(!indices[i].empty()) {
            v.push_back({indices[i].size(), -i});
        }
    }

    vector<int> ans;

    int lst = -1e9;
    for(int i = 0 ; i < n ; i++) {
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());

        if(v.size() == 1 || v[1].first == 0) {
            ans.push_back(indices[abs(v[0].second)].back());
            indices[abs(v[0].second)].pop_back();
            lst = v[0].second;

            v[0].first--;
        } else {
            if(v[0].second != lst) {
                ans.push_back(indices[abs(v[0].second)].back());
                indices[abs(v[0].second)].pop_back();
                lst = v[0].second;

                v[0].first--;
            } else {
                ans.push_back(indices[abs(v[1].second)].back());
                indices[abs(v[1].second)].pop_back();
                lst = v[1].second;
                
                v[1].first--;
            }
        }
    }

    for(int i = 0 ; i < ans.size() ; i++) {
        printf("%d%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
    }
}

int main() {
    read();
    solve();
    return 0;
}
