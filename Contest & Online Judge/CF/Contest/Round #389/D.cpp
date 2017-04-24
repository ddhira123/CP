#include <bits/stdc++.h>
using namespace std;

int n, k;
map<string,int> ms;
vector<vector<int>> v;
vector<string> vs;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n >> k;
	for(int i = 0 ; i < n ; i++) {
		string s;
		int x;
		cin >> s >> x;

		if(ms.count(s)) {
			v[ms[s]].push_back(x);
		}
		else {
			ms[s] = vs.size();
			vs.push_back(s);
			v.push_back(vector<int>());
			v[ms[s]].push_back(x);
		}
	}

	for(int i = 0 ; i < vs.size() ; i++) {
		sort(v[i].begin(),v[i].end());
		reverse(v[i].begin(),v[i].end());
	}

	int ans = 0;
	int mx = 0;

	vector<pair<int,int>> asu;

	for(int i = 0 ; i < vs.size() ; i++) {
		string s = vs[i];
		string res = s; reverse(res.begin(), res.end());

		if(s != res) {
			if(ms.count(res) && ms[res] > i) {
				int idx = ms[res];
				int mins = min(v[idx].size(), v[i].size());

				for(int j = 0 ; j < mins && v[idx][j] + v[i][j] >= 0 ; j++) {
					ans += (v[idx][j] + v[i][j]);
				}
			}
		}
		else {
			int sum = 0;
			pair<int,int> temp = {-1e9, 0};

			for(int j = 0 ; j < v[i].size() ; j++) {
				sum += v[i][j];
				if(j & 1) temp.second = max(temp.second, sum);
				else temp.first = max(temp.first,sum);
			}

			asu.push_back(temp);
		}
	}

	int tot = 0;
	// all even
	tot = 0;
	for(int i = 0 ; i < asu.size() ; i++) {
		tot += asu[i].second;
	}
	mx = max(mx, tot);
	// ada 1 ganjil
	for(int i = 0 ; i < asu.size() ; i++) {
		mx = max(mx, tot - asu[i].second + asu[i].first);
	}

	ans += mx;
	cout << ans << "\n";
	return 0;
}