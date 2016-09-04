#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 8;

int m,u,d;
string nama[N];
int pwr[N];
int size[N];
int cost[N];
int dp[N][1005][205][1][2];

int parseInt(string str) {
	int ret = 0;
	for(char x : str)
		if(x != '.')
			ret = (ret * 10) + (x - '0');
	return ret;	
}

void io(int &x) {
	string str; cin >> str;
	x = parseInt(str);
}

int solve(int pos,int duit,int sisa,int mod2,int mod3) {
	if(pos == d) return 0;
	if(duit == 0) {
		double lol = mod2 / 2.0;
		lol += (mod3 / 3.0);
		if(fabs(lol * 100 - sisa) < 1e-9) return 2;
		return 0;
	}
	if(sisa <= 0) {
		return 0;
	}
	//cout << pos << " " << duit << " " << sisa << " " << mod2 << " " << mod3 << endl;
	int &ret = dp[pos][duit][sisa][mod2][mod3];
	if(ret != -1) return ret;

	ret = solve(pos + 1,duit,sisa,mod2,mod3);
	int i = pos;
	if(duit >= cost[i]) {
		if(size[pos] == 1) ret |= solve(pos,duit - cost[i],sisa - pwr[i],mod2,mod3);
		else if(size[pos] == 2) {
			int haha = pwr[i] % 2;
			int mmod2 = (mod2 + haha);
			ret |= solve(pos,duit - cost[i],sisa - pwr[i]/2 - mmod2/2,mmod2 % 2,mod3);
		}
		else {
			int haha = pwr[i] % 3;
			int mmod3 = (mod3 + haha);
			ret |= solve(pos,duit - cost[i],sisa - pwr[i]/3 - mmod3/3,mod2,mmod3 % 3);		
		}
	}
	if(ret >= 1) ret = 1;
	return ret;
}

int pake[N];

int main() {
	io(m); io(u); io(d);
	for(int i = 0 ; i < d ; i++) {
		cin >> nama[i];
		io(pwr[i]); pwr[i] *= 10;
		string haha; cin >> haha;
		size[i] = haha.back() - '0';
		io(cost[i]);
		//cout << nama[i] << " " << pwr[i] << " " << size[i] << " " << cost[i] << "\n";
	}
	memset(dp,-1,sizeof dp);
	if(solve(0,m,u,0,0)) {
		int mod2 = 0;
		int mod3 = 0;
		for(int i = 0 ; i < d ; i++) {
			while(1) {
				//cout << i << " " << m << " " << u << " " << mod2 << " " << mod3 << endl;
				//getchar();
				if(solve(i,m,u,mod2,mod3) == 2) {
					goto hell;
				}
				if(solve(i + 1,m,u,mod2,mod3)) {
					break;
				}
				pake[i]++;
				m -= cost[i];
				if(size[i] == 1) {
					u -= pwr[i];
				}
				else if(size[i] == 2) {
					int haha = pwr[i] % 2;
					int mmod2 = (mod2 + haha);
					//cout << pwr[i]/2 << " " << mmod2/2 << endl;
					u = u - (pwr[i] / 2) - (mmod2 / 2);
					mod2 = mmod2 % 2;
				}
				else {
					int haha = pwr[i] % 3;
					int mmod3 = (mod3 + haha);
					u = u - (pwr[i] / 3) - (mmod3 / 3);
					mod3 = mmod3 % 3;
				}
			}
		}
		hell:
		for(int i = 0 ; i < d ; i++)
			if(pake[i])
				cout << nama[i] << " " << pake[i] << endl;
	}
	else {
		puts("IMPOSSIBLE");
	}
	return 0;
}