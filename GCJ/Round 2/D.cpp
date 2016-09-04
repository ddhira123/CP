#include <bits/stdc++.h>
using namespace std;

const int N = 30;

int pset[N];
bool on[N][N];
bool notYet[N];
int prv[2 * N];
int dst[2 * N];
string s[N];
int n;
int ans;
int cost[2 * N][2 * N];
int flow[2 * N][2 * N];
int sink,source;

int finds(int x) {
	return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void uni(int x,int y) {
	pset[finds(x)] = finds(y);
}

bool intersect(int a,int b) {
	for(int i = 0 ; i < n ; i++)
		if(s[a][i] == s[b][i] && s[a][i] == '1')
			return 1;
	return 0;	
}

int getCost(int a,int b) {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		if(finds(i) == a)
			ret += (s[i][b] == '0');
	return ret;	
}

int getTurn(int a) {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		ret += on[a][i];
	return ret;
}

int getSize(int a) {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		ret += (finds(i) == a);
	return ret;
}

void init() {
	for(int i = 0 ; i < n ; i++) {
		pset[i] = i;
		notYet[i] = 1;
		for(int j = 0 ; j < n ; j++)
			on[i][j] = 0;
	}
}

void read() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) {
		cin >> s[i];
		cout << s[i] << endl;
	}
}

bool kosong(int a) {
	for(int i = 0 ; i < n ; i++)
		if(s[a][i] == '1') return 0;
	return 1;
}

void gabung() {
	init();
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			if(intersect(i,j))
				uni(i,j);
}

void computeFirst() {
	ans = 0;
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			if(s[i][j] == '1') {
				notYet[j] = 0;
				on[finds(i)][j] = 1;
			}

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			ans += (on[finds(i)][j] && s[i][j] == '0');		
}
/*
void computeCost() {
	source = 2 * n;
	sink = 2 * n + 1;

	memset(flow,0,sizeof flow);
	memset(cost,0,sizeof cost);
	for(int i = 0 ; i < n ; i++)
		if(finds(i) == i && !kosong(i)) {
			if(getSize(i) <= getCost(i)) continue;
			flow[i][j] = getSize(i) - getCost(i);

			for(int j = 0 ; j < n ; j++)
				if(notYet[j]) {
					flow[n + j][sink] = 1;
					flow[i][n + j] = 1;
					cost[i][n + j] = getCost(i,j);
					cost[n + j][i] = -cost[i][n + j];
				}
		}
}

bool bellman() {
	for(int i = 0 ; i <= sink ; i++) {
		dst[i] = 1000000000;
		prv[i] = -1;
	}
	dst[source] = 0;
	for(int i = 0 ; i < sink ; i++)
		for(int j = 0 ; j <= sink ; j++)
			for(int k = 0 ; k <= sink ; k++)
				if(flow[j][k] > 0 && dst[j] + cost[j][k] < dst[k]) {
					dst[k] = dst[j] + cost[j][k];
					prv[k] = j;
				}

	return dst[sink] != 1000000000;			
}

int edmonds() {
	int ret = 0;
	while(bellman()) {
		int f = (int)1e9;
		int tot = 0;
		int cur = sink;

		while(cur != source) {
			int tmp = prv[cur];
			f = min(f,flow[tmp][cur]);
			tot += cost[tmp][cur];
			cur = tmp;
		}

		ret += f * tot;

		cur = sink;
		while(cur != source) {
			int tmp = prv[cur];
			flow[tmp][cur] -= f;
			flow[cur][tmp] += f;
			cur = tmp;
		}
	}
	return ret;
}

int computeSisa() {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		if(finds(i) == i) {
			int sz = 0;
			for(int j = 0 ; j < n ; j++)
				if(finds(j) == i) 
					sz++;
			int turn = 0;
			for(int j = 0 ; j < n ; j++)
				turn += on[i][j];
			ret += (turn - sz) * turn;		
		}
	return ret;
}*/

int lalala() {
	int udah = 0;
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		if(finds(i) == i && !kosong(i)) {
			int turn = getTurn(i);
			int size = getSize(i);
			if(turn >= size)
				ret += turn * (turn - size);
			else
				ret += size * (size - turn);
			udah += max(turn,size);
		}
	ret += (n - udah);	
	return ret;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		gabung();
		computeFirst();
		ans += lalala();
		printf("Case #%d: %d\n",tc,ans);
	}
	return 0;
}