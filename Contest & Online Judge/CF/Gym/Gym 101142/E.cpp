#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

typedef long long LL;
const LL B1 = 31;
const LL B2 = 16249;
const LL MOD1 = 1e9 + 9;
const LL MOD2 = 109026347;

LL modPow(LL base,LL po,LL mod) {
	LL ret = 1 % mod;
	while(po) {
		if(po & 1) ret = ret * base % mod;
		base = base * base % mod;
		po >>= 1;
	}
	return ret;
}

vector<int> idx;
vector<int> R;
vector<int> C;
vector<LL> H1, H2;
int len;
string s;
vector<string> v;
int r, c;
string dummy;
int minsr, minsc;
LL T1, T2;
LL S1, S2;
int active;
map<pair<int,int>,int> touched;
multiset<int> forR, forC;
int cross;
LL INVER1, INVER2, INVEC1, INVEC2;

void read() {
	cin >> len;
	getline(cin,dummy);
	getline(cin,s);
	cin >> r >> c;
	getline(cin,dummy);
	for(int i = 0 ; i < r ; i++) {
		getline(cin,dummy);
		v.push_back(dummy);
	}
}

int countCross() {
	int ret = 0;
	for(string x : v)
		for(char c : x)
			if(c == 'X')
				ret++;
	return ret;
}

void prec() {
	cross = countCross();
	assert(cross >= 2);
	minsr = r + 1;
	minsc = c + 1;
	for(int i = 0 ; i < v.size() ; i++)
		for(int j = 0 ; j < v[i].length() ; j++)
			if(v[i][j] == 'X') {
				minsr = min(minsr,i);
				minsc = min(minsc,j);
			}
	for(int i = 0 ; i < v.size() ; i++)
		for(int j = 0 ; j < v[i].length() ; j++)
			if(v[i][j] == 'X') {
				int normr = i - minsr;
				int normc = j - minsc;
				T1 = (T1 + modPow(B1,normr,MOD1) * modPow(B2,normc,MOD1)) % MOD1;
				T2 = (T2 + modPow(B1,normr,MOD2) * modPow(B2,normc,MOD2)) % MOD2;
			}		
	idx.push_back(-1);
	R.push_back(0);
	C.push_back(0);

	for(int i = 0 ; i < s.length() ; i++)
		if(s[i] == 'u') {
			idx.push_back(i);
			R.push_back(R.back()-1);
			C.push_back(C.back());
		}
		else if(s[i] == 'd') {
			idx.push_back(i);
			R.push_back(R.back()+1);
			C.push_back(C.back());
		}
		else if(s[i] == 'l') {
			idx.push_back(i);
			R.push_back(R.back());
			C.push_back(C.back()-1);
		}
		else if(s[i] == 'r') {
			idx.push_back(i);
			R.push_back(R.back());
			C.push_back(C.back()+1);
		}

	minsr = 1e9;
	minsc = 1e9;
	for(int i = 0 ; i < R.size() ; i++) {
		minsr = min(minsr,R[i]);
		minsc = min(minsc,C[i]);
	}	

	for(int i = 0 ; i < R.size() ; i++) {
		R[i] -= minsr;
		C[i] -= minsc;
		H1.push_back(modPow(B1,R[i],MOD1) * modPow(B2,C[i],MOD1) % MOD1);
		H2.push_back(modPow(B1,R[i],MOD2) * modPow(B2,C[i],MOD2) % MOD2);
	}

	INVER1 = modPow(B1,MOD1-2,MOD1);
	INVEC1 = modPow(B2,MOD1-2,MOD1);

	INVER2 = modPow(B1,MOD2-2,MOD2);
	INVEC2 = modPow(B2,MOD2-2,MOD2);

	//printf("%lld %lld\n",INVER2,INVER2 * B1 % MOD2);
}

void add(int rr,int cc) {
	if(touched[{rr,cc}] == 0) {
		active++;
		S1 = (S1 + modPow(B1,rr,MOD1) * modPow(B2,cc,MOD1)) % MOD1;
		S2 = (S2 + modPow(B1,rr,MOD2) * modPow(B2,cc,MOD2)) % MOD2;
	}
	touched[{rr,cc}]++;
	forR.insert(rr);
	forC.insert(cc);
}

void remove(int rr,int cc) {
	if(touched[{rr,cc}] == 1) {
		active--;
		S1 = (S1 - modPow(B1,rr,MOD1) * modPow(B2,cc,MOD1)) % MOD1;
		S2 = (S2 - modPow(B1,rr,MOD2) * modPow(B2,cc,MOD2)) % MOD2;
		if(S1 < 0) S1 += MOD1;
		if(S2 < 0) S2 += MOD2;
	}
	touched[{rr,cc}]--;
	auto it = forR.lower_bound(rr);
	forR.erase(it);
	it = forC.lower_bound(cc);
	forC.erase(it);
}

void remover(int rr,int cc) {
	remove(R[0],C[0]);
	R[0] = rr;
	C[0] = cc;
}

int getMinR() {
	auto it = forR.begin();
	return *it;
}

int getMinC() {
	auto it = forC.begin();
	return *it;
}

bool solve() {
	add(R[0],C[0]);

	int lo = 1;
	for(int hi = 1 ; hi < idx.size() ; hi++) {
		add(R[hi], C[hi]);
		while(active > cross) {
			remover(R[lo], C[lo]);
			lo++;
		}

		LL SS1, SS2;
		minsr = getMinR();
		minsc = getMinC();

		SS1 = (S1 * modPow(INVER1,minsr,MOD1) % MOD1);
		SS1 = (SS1 * modPow(INVEC1,minsc,MOD1) % MOD1);

		SS2 = (S2 * modPow(INVER2,minsr,MOD2) % MOD2);
		SS2 = (SS2 * modPow(INVEC2,minsc,MOD2) % MOD2);

		//printf("lo %d hi %d idx[] %d minsr %d minsc %d SS1 %lld SS2 %lld\n",lo,hi,idx[hi],minsr,minsc,SS1,SS2);
		//printf("%lld %lld\n",T1,T2);
		if(active == cross && T1 == SS1 && T2 == SS2) {
			puts("YES");
			printf("%d %d\n",idx[lo]+1, idx[hi]+1);
			return 1;
		}
	}
	return 0;
}

int main() {
	OPEN("easy");
	read();
	prec();
	if(!solve()) puts("NO");
	CLOSE();
	return 0;
}