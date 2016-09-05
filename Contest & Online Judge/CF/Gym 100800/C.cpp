#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

set<pair<string,string> > message;
set<string> id;
map<string,int> used;
map<string,int> cnt;

vector<string> parse(string str) {
	stringstream ss;
	ss << str;
	vector<string> ret;
	string temp;
	while(ss >> temp) {
		ret.push_back(temp);
	}
	return ret;
}

bool cmp(pair<int,string> a,pair<int,string> b) {
	if(a.fi == b.fi) return a.se < b.se;
	return a.fi > b.fi;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL);

	int n; cin >> n;
	string str;
	getline(cin,str);
	for(int i = 0 ; i < n ; i++) {
		getline(cin,str);
		vector<string> parsed = parse(str);
		string user = parsed[0];
		id.insert(user);

		for(int j = 1 ; j < parsed.size() ; j++) {
			string temp = parsed[j];
			cnt[temp]++;
			if(!message.count({user,temp})) used[temp]++;
			message.insert({user,temp});
		}
	}

	vector<pair<int,string> > ok;
	for(auto it : used) {
		if(it.se == id.size()) {
			string temp = it.fi;
			ok.push_back({cnt[temp],temp});
		}
	}

	sort(ok.begin(),ok.end(),cmp);
	if(ok.empty())
		cout << "ALL CLEAR\n";
	else {
		for(pair<int,string> x : ok)
			cout << x.se << "\n";
	}
	return 0;
}