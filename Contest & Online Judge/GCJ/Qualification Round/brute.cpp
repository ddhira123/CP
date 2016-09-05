#include <bits/stdc++.h>
using namespace std;

string expand(string ori,long long c) {
	string ret = ori;
	string g = "";
	for(long long i = 0 ; i < ori.length() ; i++) g += "1";

	for(long long i = 1 ; i < c ; i++) {
		string temp = "";
		for(long long i = 0 ; i < ret.length() ; i++)
			if(ret[i] == '0')
				temp += ori;
			else
				temp += g;
		ret = temp;	
	}
	return ret;
}

long long getMask(string s) {
	reverse(s.begin(),s.end());
	long long ret = 0;
	for(long long i = 0 ; i < s.length() ; i++)
		ret += (((1ll*s[i]-'0')) << i);
	return ret;
}

string convertToString(long long x,long long len) {
	string ret = "";
	while(x) {
		ret += ((x%2) + '0');
		x /= 2;
	}
	while(ret.length() < len) ret += "0";
	reverse(ret.begin(),ret.end());
	return ret;
}

vector<long long> convertToList(long long x) {
	vector<long long> ret;
	for(long long i = 0 ; (1ll << i) <= x ; i++)
		if((1ll<<i) & x)
			ret.push_back(i);
	return ret;	
}

int main() {
	//while(1) {
	for(long long k = 2 ; k <= 25 ; k++) for(long long c = 1, mul = k; mul <= 60 ; mul *= k, c++) {
		//long long k,c;
		//cin >> k >> c;
		vector<long long> all;
		long long total_length = 0;

		for(long long i = 1 ; i < (1ll << k) ; i++) {
			string expanded = expand(convertToString(i,k),c);
			total_length = expanded.length();
			//cout << expanded << " " << getMask(expanded) << endl;
			all.push_back(getMask(expanded));
		}

		vector<long long> mins;

		for(long long i = 1 ; i < (1ll<<total_length) ; i++) {
			if(!mins.empty() && __builtin_popcountll(i) >= mins.size()) continue;
			bool ok = 1;
			for(long long x : all) {
				ok &= ((x & i) > 0);
				if(!ok) {
					break;
				}
			}
			if(ok) {
				vector<long long> v = convertToList(i);
				if(mins.empty() || v.size() < mins.size()) mins = v;
			}
		}

		cout << k << " " << c << ": ";
		for(long long x : mins) cout << x << " ";
		cout << endl;
	}
	return 0;
}