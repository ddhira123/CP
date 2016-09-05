#include <bits/stdc++.h>
using namespace std;

const string SRC = "Ahmad";
const int INF = 1e9;

map<string,vector<string>> adj;
map<string,int> dst;

void init() {
	adj.clear();
	dst.clear();
}

void read() {
	int n; cin >> n;
	for(int i = 0 ; i < n ; i++) {
		string s[3];
		for(int j = 0 ; j < 3 ; j++) {
			cin >> s[j];
			dst[s[j]] = INF;
		}
		for(int j = 0 ; j < 3 ; j++)
			for(int k = 0 ; k < 3 ; k++)
				if(j != k)
					adj[s[j]].push_back(s[k]);
	}
}

void BFS() {
	queue<string> q;
	dst[SRC] = 0;
	q.push(SRC);

	while(!q.empty()) {
		string now = q.front();
		vector<string> nxt = adj[now];
		q.pop();

		for(string nex : nxt)
			if(dst[nex] == INF) {
				dst[nex] = dst[now]+1;
				q.push(nex);
			}
	}
}

void output() {
	vector<pair<int,string>> v;
	for(auto it : dst) {
		int dist = it.second;
		string name = it.first;
		v.push_back({dist,name});
	}
	sort(v.begin(),v.end());

	cout << v.size() << "\n";
	for(pair<int,string> x : v) {
		cout << x.second << " ";
		if(x.first == INF) cout << "undefined\n";
		else cout << x.first << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		init();
		read();
		BFS();
		output();
	}
	return 0;
}