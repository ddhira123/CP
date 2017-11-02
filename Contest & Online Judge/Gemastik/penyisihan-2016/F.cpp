#include <bits/stdc++.h>
using namespace std;

char persen = '%';

int getIndex(char x) {
	if('1' <= x && x <= '9') return x - '0';
	if(x == 'T') return 10;
	if(x == 'J') return 11;
	if(x == 'Q') return 12;
	if(x == 'K') return 13;
	return 14;
}

int getSuite(char x) {
	if(x == 'D') return 0;
	if(x == 'C') return 1;
	if(x == 'H') return 2;
	return 3;
}

long long modPow(int a,int b) {
	long long ret = 1;
	for(int i = 0 ; i < b ; i++)
		ret *= a;
	return ret;
}

long long dp[13][13][13][13][13][2][2][2];
long long cara[13][13];
long long com[50][50];
int total;

long long solve(int kurang,int lebih,int A,int B,int C,int a,int b,int c) {
	if(kurang + lebih == 0) {
		if(a+b+c > 0) return 0;
		int sisa = 39 - total;
		return com[sisa][13-A] * com[sisa-(13-A)][13-B];
	}
	long long &ret = dp[kurang][lebih][A][B][C][a][b][c];
	if(ret != -1) return ret;

	ret = 0;
	if(lebih > 0) {
		ret = solve(kurang,lebih-1,A+1,B,C,1,b,c) + solve(kurang,lebih-1,A,B+1,C,a,1,c) + solve(kurang,lebih-1,A,B,C+1,a,b,1);
	}
	else {
		ret = solve(kurang-1,0,A+1,B,C,0,b,c) + solve(kurang-1,0,A,B+1,C,a,0,c) + solve(kurang-1,0,A,B,C+1,a,b,0);
	}
	return ret;
}

void prec() {
	for(int i = 0 ; i < 50 ; i++) {
		com[i][0] = 1;
		for(int j = 1 ; j <= i ; j++)
			com[i][j] = com[i-1][j] + com[i-1][j-1];
	}
	for(total = 0 ; total < 13 ; total++) {
		memset(dp,-1,sizeof dp);
		for(int i = 0 ; i <= total ; i++)
			cara[i][total-i] = solve(i,total-i,0,0,0,0,0,0);
	}
}

string ori[15];
int idx[50], suite[50];
int ada[50][5];
int cSuite[5];
double ans[15];

void read() {
	for(int i = 0 ; i < 13 ; i++) {
		cin >> ori[i];
		idx[i] = getIndex(ori[i][0]);
		suite[i] = getSuite(ori[i][1]);
		//cout << ori[i] << " " << idx[i] << " " << suite[i] << endl;
	}
}

void solve() {
	memset(ada,0,sizeof ada);
	memset(cSuite,0,sizeof cSuite);

	for(int i = 0 ; i < 13 ; i++) {
		ada[idx[i]][suite[i]] = 1;
		cSuite[suite[i]]++;
	}

	for(int i = 0 ; i < 13 ; i++) {
		int kurang = 0;
		int lebih = 0;
		for(int j = 2 ; j <= 14 ; j++)
				if(!ada[j][suite[i]]) {
					if(j < idx[i]) kurang++;
					else lebih++;
				}

		//cout << i << " " << lebih << " " << kurang << endl;
		//printf("%lld %lld\n",solve(kurang,lebih,0,0,0), modPow(3,kurang+lebih));
		ans[i] = 100.0 * (double)cara[kurang][lebih] / (com[39][13] * com[26][13]);		
	}

	for(int i = 0 ; i < 13 ; i++)
		printf("%s: %.5lf%c\n",ori[i].c_str(),ans[i],persen);
}

int main() {
	memset(dp,-1,sizeof dp);
	prec();

	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		solve();

		if(tc < t) printf("\n");
	}
	return 0;
}