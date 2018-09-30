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

    priority_queue<pair<int, int>> pq;
    int mx = 1;
    for(int i = 2 ; i <= n ; i++) {
        if(indices[mx].size() < indices[i].size()) {
            mx = i;
        }
    }

    for(int i = 1 ; i <= n ; i++) {
        if(i == mx) {
            pq.push({indices[i].size(), i});
        } else if(!indices[i].empty()) {
            pq.push({indices[i].size(), -i});
        }
    }

    vector<int> ans;

    int lst = -1e9;
    while(!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();

        if(pq.size() == 0) {
            ans.push_back(indices[abs(cur.second)].back());
            indices[abs(cur.second)].pop_back();
            lst = cur.second;

            if(cur.first != 1) {
                pq.push({cur.first - 1, cur.second});
            }
        } else {
            if(cur.second != lst) {
                ans.push_back(indices[abs(cur.second)].back());
                indices[abs(cur.second)].pop_back();
                lst = cur.second;

                if(cur.first != 1) {
                    pq.push({cur.first - 1, cur.second});
                }
            } else {
                pair<int, int> temp = cur;
                cur = pq.top();
                pq.pop();

                ans.push_back(indices[abs(cur.second)].back());
                indices[abs(cur.second)].pop_back();
                lst = cur.second;

                pq.push(temp);
                if(cur.first != 1) {
                    pq.push({cur.first - 1, cur.second});
                }
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