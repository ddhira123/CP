#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int ans[125];
int n;

void rec() {
    int las = v.back();
    if(las > n || v.size() > ans[las]) return;
    ans[las] = v.size();

    for(int i = v.size() - 1 ; i >= 0 ; i--)
        for(int j = i ; j >= 0 ; j--) {
            int newVal = v[i] + v[j];
            if(newVal > las) {
                v.push_back(newVal);
                rec();
                v.pop_back();
            }
        }
}

int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) ans[i] = (int)1e9;
    v.push_back(1);
    rec();
    cout << ans[n] - 1 << endl;
    return 0;
}
