#include <bits/stdc++.h>
using namespace std;

const int N = 105;

string s[N];
vector<int> adj[26];
int deg[26];
int permut[N];
int n;

void read() {
	cin >> n;
	for(int i = 1 ; i<= n ; i++)
		cin >> s[i];
	for(int i = 1 ; i<= n ;i++)
		cin >> permut[i];
}

void init() {
	for(int i = 1 ; i+1 <= n ; i++) {
		int a = permut[i];
		int b = permut[i+1];
		int len = min(s[a].length(),s[b].length());
		int it = 0;

		while(it < len && s[a][it] == s[b][it]) it++;
		if(it == len) {
			if(s[a].length() > s[b].length()) {
				cout << "NE\n";
				exit(0);
			}
		}
		else {
			//cout << s[a][it] << " " << s[b][it] << "\n";
			int cha = s[a][it] - 'a';
			int chb = s[b][it] - 'a';
			deg[chb]++;
			adj[cha].push_back(chb);
		}
	}
}

void solve() {
	vector<int> ret;
	queue<int> q;

	for(int i = 0 ; i < 26 ; i++)
		if(deg[i] == 0)
			q.push(i);

	while(!q.empty()) {
		int now = q.front();
		q.pop();
		ret.push_back(now);

		for(int nex : adj[now]) {
			deg[nex]--;
			if(deg[nex] == 0)
				q.push(nex);
		}
	}	

	if(ret.size() == 26) {
		cout << "DA\n";
		int ans[26];
		for(int i = 0 ; i < 26 ; i++)
			ans[ret[i]] = i;
		for(int i = 0 ; i < 26 ; i++)
			cout << (char)(ans[i]+'a');
		cout << "\n";
	}
	else {
		cout << "NE\n";
	}
}

int main() {
	read();
	init();
	solve();
	return 0;
}