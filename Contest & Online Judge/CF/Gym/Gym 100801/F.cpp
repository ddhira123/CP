#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

vector<string> command;
vector<int> spasi;
vector<int> nxt;

map<string, pair<LL,LL>> get(string a,pair<LL,LL> mul,string substitute) {
	map<string, pair<LL, LL>> ret;
	string satu = substitute;
	string dua = satu + substitute;
	string tiga = dua + substitute;
	string empat = tiga + substitute;
	string lima = empat + substitute;
	string enam = lima + substitute;

	if(a.length() == 1) {
		ret[dua] = {1, 2};
		ret[satu] = {-1, 2};
	} else if(a.length() == 2) {
		ret[tiga] = {1, 3};
		ret[dua] = {-1, 2};
		ret[satu] = {1, 6};
	} else if(a.length() == 3) {
		ret[empat] = {1, 4};
		ret[tiga] = {-1, 2};
		ret[dua] = {1, 4};
	} else if(a.length() == 4) {
		ret[lima] = {1, 5};
		ret[empat] = {1, 2};
		ret[tiga] = {1, 3};
		ret[satu] = {-1, 30}; 
	} else if(a.length() == 5) {

	} else {
		assert(0);
	}

	return ret;
}

map<string, pair<LL, LL>> expand(map<string, pair<LL, LL>> x, string substitute) {
	map<string, pair<LL, LL>> ret;

	return ret;
}

void makeNext() {
	for(int i = 0 ; i < command.size() ; i++) {
		int tb = 0;
		while(command[i][tb] == ' ') {
			tb++;
		}
		spasi.push_back(tb);
		command[i].erase(command[i].begin(), command[i].begin() + tb);

		for(int j = i-1 ; j >= 0 ; j--)
			if(spasi[j] + 4 == tb) {
				nxt[j].push_back(j);
				break;
			}
	}
}

int main() {

	string s;
	while(getline(cin, s)) {
		command.push_back(s);
	}
	return 0;
}