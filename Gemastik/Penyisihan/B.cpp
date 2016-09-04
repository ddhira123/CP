#include <bits/stdc++.h>
using namespace std;

const int MX = 24*60*60+5;
const int N = 50005;

typedef pair<int,int> pii;
#define fi first
#define se second

char dummy[N];

string readString() {
	scanf("%s",dummy);
	return (string)dummy;
}

int convertToInt(string str) {
	int jam = 10*(str[0] - '0') + str[1] - '0';
	int menit = 10*(str[3] - '0') + str[4] - '0';
	int sekon = 10*(str[6] - '0') + str[7] - '0';

	return jam*3600 + menit*60 + sekon;
}

bool cmp(pair<pii,int> a,pair<pii,int> b) {
	if(a.fi.fi == b.fi.fi)
		return a.fi.se > b.fi.se;
	return a.fi.fi < b.fi.fi;
}

pii ori[N];
pair<pii,int> sorted[N];
vector<int> satu;
int sum[MX];
bool covered[N];
int n;

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		ori[i].fi = convertToInt(readString());
		ori[i].se = convertToInt(readString());

		sorted[i] = {ori[i],i};
	}
}

void makeOne() {
	memset(sum,0,sizeof sum);
	for(int i = 1 ; i <= n ; i++) {
		sum[ori[i].fi]++;
		sum[ori[i].se]--;
	}

	satu.clear();
	if(sum[0] == 1) satu.push_back(0);
	for(int i = 1 ; i < MX ; i++) {
		sum[i] += sum[i-1];
		if(sum[i] == 1) satu.push_back(i);
	}
}

void makeCovered() {
	memset(covered,0,sizeof covered);
	sort(sorted + 1,sorted + n + 1,cmp);
	int mx = -1;

	for(int i = 1 ; i <= n ; i++) {
		if(mx >= sorted[i].fi.se || (i<n && sorted[i].fi == sorted[i+1].fi)) covered[sorted[i].se] = 1;
		mx = max(mx,sorted[i].fi.se);
	}
}

void solve() {
	makeCovered();
	makeOne();

	for(int i = 1 ; i <= n ; i++) {
		int ans = -1;
		if(!covered[i]) {
			int idx = lower_bound(satu.begin(),satu.end(),ori[i].fi) - satu.begin();
			if(idx >= satu.size() || satu[idx] >= ori[i].se)
				ans = 2;
			else
				ans = 1;
		}
		printf("%d\n",ans);
	}
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		solve();
	}
	return 0;
}