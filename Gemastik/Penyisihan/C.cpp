#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 50005;

char dummy[N];

string readString() {
	scanf("%s",dummy);
	return (string)dummy;
}

pair<int,pii> orang[N];
string str[N];
pii ori[N];

bool udah[15];
int urutan[15];
int ans[15];
long long best;
vector<int> impoten;
int n;

bool byGanteng(pair<int,pii> a, pair<int,pii> b) {
	return a.se.fi > b.se.fi;
}

bool byCantik(pair<int,pii> a, pair<int,pii> b) {
	return a.se.se > b.se.se;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		str[i] = readString();
		scanf("%d %d",&ori[i].fi,&ori[i].se);
		orang[i] = {i,ori[i]};
	}
}

void rec(int idx,long long a,long long b) {
	if(idx == 7) {
		if(a + b > best) {
			best = a+b;
			for(int i = 1 ; i <= 6 ; i++)
				ans[i] = urutan[i];
		}
		return;
	}
	for(int i = 0 ; i < impoten.size() ; i++)
		if(!udah[i]) {
			udah[i] = 1;
			urutan[idx] = impoten[i];
			if(idx <= 3) rec(idx+1,a * ori[impoten[i]].fi,b);
			else		 rec(idx+1,a,b * ori[impoten[i]].se);
			udah[i] = 0;
		}
}

void solve() {
	impoten.clear();

	sort(orang + 1,orang + n + 1,byGanteng);
	for(int i = 1 ; i <= 6 ; i++) impoten.push_back(orang[i].fi);

	sort(orang + 1,orang + n + 1,byCantik);
	for(int i = 1 ; i <= 6 ; i++) impoten.push_back(orang[i].fi);

	sort(impoten.begin(),impoten.end());
	impoten.erase(unique(impoten.begin(),impoten.end()),impoten.end());

	best= -1;
	rec(1,1,1);

	printf("%lld\n",best);
	for(int i = 1 ; i <= 6 ; i++)
		printf("%s%c",str[ans[i]].c_str(),i % 3 == 0 ? '\n' : ' ');
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		solve();
	}
	return 0;
}