#include <bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 5;

map<string , string> val;
map<string, vector<string>> adj;
set<string> seen;
vector<string> ans;
int n;

void build(int i,string str) {
	stringstream ss;
	ss << str;

	vector<string> tmp;

	while(ss >> str) {
		if(str == "with" || str == "def" || str == "=") {
			continue;
		}
		tmp.push_back(str);
	}

	string haha = tmp[0];
	tmp.erase(tmp.begin());
	val[haha] = tmp.back();
	tmp.pop_back();

	for(string x : tmp)
		adj[haha].push_back(x);
	reverse(adj[haha].begin(), adj[haha].end());
}

void traverse(string str) {
	if(seen.count(str)) {
		return;
	}
	seen.insert(str);
	for(string nex : adj[str])
		traverse(nex);
	ans.push_back(val[str]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	string str;
	getline(cin, str);
	for(int i = 0 ; i < n ; i++) {
		getline(cin, str);
		build(i, str);
	}
	cin >> str;

	traverse(str);

	reverse(ans.begin(), ans.end());
	for(string x : ans)
		cout << x << " ";
	return 0;
}