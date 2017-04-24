#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

vector<string> parse(string str) {
	vector<string> v;
	string s;
	for(int i = 0 ; i < str.length() ; i++)
		if(str[i] == '-') {
			v.push_back(s);
			s = "";
		}
		else {
			s += str[i];
		}
	v.push_back(s);
	return v;	
}

vector<char> hard = {'b','c','d','g','k','n','p','t'};
vector<char> cons = {'a','i','u','e','o'};
vector<char> en = {'a','o','u'};

char toLower(char x) {
	if(x <= 'Z') return x - 'A' + 'a';
	return x;
}

char toUpper(char x) {
	if(x <= 'Z') return x;
	return x -'a' + 'A';
}

bool isUpper(char x ){
	return x <= 'Z';
}

bool isHard(char x) {
	for(char z : hard)
		if(x == z) return 1;
	return 0;
}

bool isCons(char x) {
	for(char z : cons)
		if(x == z) return 1;
	return 0;
}

int getDist(char a,char b) {
	return abs((int)a - (int)b);
}

char nearHard(char x) {
	int mins = 100;
	int best = 0;

	for(char z : hard) {
		int dst = getDist(x,z);
		if(dst < mins) {
			mins = dst;
			best = z;
		}
	}

	return best; 	
}

char nearEnd(char x) {
	int mins = 100;
	char best = 'x';

	for(char z : en) {
		int dst = getDist(x,z);
		if(dst < mins) {
			mins = dst;
			best = z;
		}
	}

	return best; 	
}

string convert(vector<string> v) {
	string ret = v[0];
	if(1) {
		char nearest = nearHard(toLower(ret[0]));
		if(isUpper(ret[0]))
			ret[0] = toUpper(nearest);
		else
			ret[0] = nearest;
		v[0] = ret;
		//cout << v[0] << "\n";
	}
	char lst = toLower(v[0][0]);

	ret = "";
	for(string str : v) ret += str;
	for(int i = v[0].size() ; i < ret.length() ; i++)
		if(isHard(toLower(ret[i])))
			ret[i] = lst;
	//cout << ret << endl;
	if(isHard(toLower(ret.back()))) {
		ret += nearEnd(toLower(ret.back()));
		ret += "h";
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	bool space = 0;
	string str;
	while(cin >> str) {
		if(space) cout << " ";
		else space = 1;
		//cout << "STR " << str << endl;
		vector<string> parsed = parse(str);
		string ret = convert(parsed);
		cout << ret;		
	}
	cout << "\n";
	return 0;
}