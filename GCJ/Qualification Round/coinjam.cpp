#include <bits/stdc++.h>
using namespace std;

const int LIM = 33333335;

string decToBinary(int x) {
	string ret = "";
	while(x) {
		ret += ((x % 2) + '0');
		x /= 2;
	}
	reverse(ret.begin(),ret.end());
	//assert(ret[0] == '1' && ret[ret.length()-1] == '1' && ret.length() == 16);
	return ret;
}

long long convert(string &s,long long base) {
	long long ret = 0;
	for(int i = 0 ; i < s.length() ; i++) {
		ret *= base;
		if(s[i] == '1') ret++;
	}
	return ret;
}

vector<int> primes;
bool flag[LIM + 5];

void sieve() {
	for(int i = 2 ; i <= LIM ; i++)
		if(!flag[i]) {
			primes.push_back(i);
			//cerr << i << endl;
			for(int j = i ; j <= LIM ; j += i)
				flag[j] = 1;
		}
	//cerr << primes.size() << endl;	
}

long long getDivisor(long long x) {
	//if(x < (long long)primes.back() && binary_search(primes.begin(),primes.end(),(int)x))
	//	return -1;
	for(int y : primes) {
		if(x % (long long)y == 0) return y;
		if((long long)y * y > x) return -1;
	}
	return -1;
}

vector<int> getListDivisor(string s) {
	//cout << "a\n";
	vector<int> v;
	for(int i = 2 ; i <= 10 ; i++) {
		int divisor = getDivisor(convert(s,i));
		//cout << divisor << endl;
		if(divisor == -1) return v;
		v.push_back(divisor);
	}
	return v;
}

int main() {
	sieve();
	printf("Case #1:\n");
	for(int i = (1<<15) + 1, done = 0 ; done < 50 ; i += 2) {
		string s = decToBinary(i);
		//cerr << i << " " << s << " " << done << endl;
		vector<int> v = getListDivisor(s);
		if(v.size() == 9) {
			cout << s;
			//cerr << s << endl;
			for(int divisor : v)
				cout << " " << divisor;
			cout << endl;
			done++;
		}
	}
	return 0;
}