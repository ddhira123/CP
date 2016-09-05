#include <bits/stdc++.h>
using namespace std;

bool isDecimal(string x) {
	if(x[0] == '-') {
		if(x.length() == 1) return 0;
		if(x[1] < '1' || x[1] > '9') return 0;
		for(int i = 1 ; i < x.length() ; i++)
			if('0' > x[i] || x[i] > '9') return 0;
		return 1;			
	}
	if(x[0] == '0') {
		return x.length() == 1;
	}
	for(int i = 0 ; i < x.length() ; i++)
		if('0' > x[i] || x[i] > '9') {
			//cout << x[i] << endl;
			return 0;
		}
	return 1;
}

string nega(string x) {
	const int BAWAH = ((1<<31) / 2) * 2;
	const long long B = BAWAH;

	long long now = 0;
	for(int i = 1 ; i < x.length() ; i++) {
		now *= 10LL;
		now += (x[i] - '0');
		if(-now < B) return "WA";
	}
	return "AC";
}

string posi(string x) {
	const int ATAS = (((1ll<<31) - 1) / 2) * 2;
	const long long A = ATAS;

	long long now = 0;
	for(int i = 0 ; i < x.length() ; i++) {
		now *= 10LL;
		now += (x[i] - '0');
		if(now > A) return "WA";
	}
	return "AC";
}


string satu() {
	string s; getline(cin,s);
	if(!isDecimal(s)) return "WA";
	//cout << "aa";
	if(s[0] == '-') return nega(s);
	return posi(s);
}

const long long MOD = (long long)1e9 + 7;
const long long MAGIC = 10007;

long long modPow(long long base,int pwr) {
	long long res = 1;
	while(pwr) {
		if(pwr & 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		pwr >>= 1;
	}
	return res;
}

int getID(int x) {
	return x + 1;
}

long long hashed[1000005];
long long po[1000005];
long long inve[1000005];

long long getHashed(int l,int r) {
	long long ret = hashed[r] - hashed[l - 1];
	ret = (ret * inve[l - 1]) % MOD;
	if(ret < 0) ret += MOD;
	//if(l == 1) cerr << hashed[r] << " " << hashed[l - 1] << " " << inve[l - 1] << endl;
	return ret;
}

string dua() {
	po[0] = inve[0] = 1;
	long long inv = modPow(MAGIC, MOD - 2);

	for(int i = 1 ; i <= 1000000 ; i++) {
		po[i] = (MAGIC * po[i - 1]) % MOD;
		inve[i] = (inv * inve[i - 1]) % MOD;
	}

	string s; getline(cin,s);
	if(s.length() % 2 != 0) return "WA";

	s = "X" + s;
	for(int i = 1 ; i < s.length() ; i++) {
		hashed[i] = (hashed[i - 1] + po[i] * getID(s[i])) % MOD;
	}

	for(int i = 1 ;  ; i++) {
		int kiri = i;
		int kanan = s.length() - i;
		int sisa = kanan - kiri - 1;
		if(sisa == 0) break;
		sisa /= 2;
		//cerr << kiri << " " << kanan << endl;
		//cerr << getHashed(1,kiri) << " " << getHashed(kanan,s.length() - 1) << endl;
		if(getHashed(1,kiri) != getHashed(kanan,s.length() - 1)) continue;
		if(getHashed(kiri + 1,kiri + sisa) != getHashed(kiri + sisa + 1,kanan - 1)) continue;
		return "AC";
	}

	return "WA";
}

int main() {
	int tipe; cin >> tipe; getchar();
	string ans = "AYAZGANTENG";
	if(tipe == 2)
    	ans = dua();
    else
    	ans = satu();
    cout << ans << endl;
    return 0;
}