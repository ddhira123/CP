#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 32000000;

bool flag[MAGIC];
vector<int> primes;

void init() {
	for(int i = 2 ; i < MAGIC ; i++)
		if(!flag[i]) {
			primes.push_back(i);
			for(int j = i ; j < MAGIC / i ; j++)
				flag[i*j] = 1;
		}
}

bool isPrime(long long x) {
	if(x <= 1) return 0;
	for(int i = 0 ; primes[i] <= x / primes[i] ; i++)
		if(x % primes[i] == 0) return 0;
	return 1;
}

map<int,int> cnt[2];
map<int,long long> prv[2];
map<int,int> dst[2];
long long a, b;

void bfs(int id) {
	queue<long long> q;
	q.push(id ? b : a);
	cnt[id][q.front()] = 1;
	dst[id][q.front()] = 0;

	while(!q.empty()) {
		long long now = q.front();
		q.pop();
		//printf("%d %lld %lld\n",id,now,prv[id][now]);

		if(isPrime(now-2)) {
			if(!dst[id].count(now-2)) {
				dst[id][now-2] = dst[id][now]+1;
				cnt[id][now-2] = cnt[id][now];
				prv[id][now-2] = now;
				q.push(now-2);
			}
			else if(dst[id][now-2] == dst[id][now]+1)
				cnt[id][now-2] = 2;
		}

		if(isPrime(now+2)) {
			if(!dst[id].count(now+2)) {
				dst[id][now+2] = dst[id][now]+1;
				cnt[id][now+2] = cnt[id][now];
				prv[id][now+2] = now;
				q.push(now+2);
			}
			else if(dst[id][now+2] == dst[id][now]+1)
				cnt[id][now+2] = 2;
		}

		if(isPrime(now-2)) {
			if(!dst[id].count(2)) {
				dst[id][2] = dst[id][now]+1;
				cnt[id][2] = cnt[id][now];
				prv[id][2] = now;
				q.push(2);
			}
			else if(dst[id][2] == dst[id][now]+1)
				cnt[id][2] = 2;
		}
	}
}

vector<long long> fetch(int id,long long x,long long y) {
	vector<long long> ret;
	while(x != y) {
		ret.push_back(y);
		y = prv[id][y];
	}
	ret.push_back(x);
	return ret;
}

void solve() {
	bfs(0);
	bfs(1);

	int minstep = 1000000000;
	int way = 0;

	if(dst[0].count(b)) minstep = dst[0][b], way = cnt[0][b];
	if(dst[0].count(2) && dst[1].count(2)) {
		//printf("masuk\n");
		if(minstep > dst[0][2] + dst[1][2]) {
			minstep = dst[0][2] + dst[1][2];
			way = cnt[0][2] * cnt[1][2];
		}
		else if(minstep == dst[0][2] + dst[1][2]) {
			way += cnt[0][2] * cnt[1][2];
		}
	}
	//printf("%d\n",way);
	if(minstep == 1000000000) {
		printf("Unlucky Benny\n");
	}
	else if(way > 1)
		printf("Poor Benny\n");
	else {
		if(dst[0].count(b) && minstep == dst[0][b]) {
			vector<long long> path = fetch(1,b,a);
			for(int i = 0 ; i+1 < path.size() ; i++)
				printf("%lld->",path[i]);
			printf("%lld\n",b);
		}
		else {
			vector<long long> path = fetch(0,a,2);
			vector<long long> path2 = fetch(1,b,2);
			reverse(path.begin(),path.end());

			for(int i = 0 ; i < path.size() ; i++) printf("%lld->",path[i]);
			for(int i = 1 ; i+1 < path2.size() ; i++) printf("%lld->",path2[i]);
			printf("%lld\n",b);
		}
	}
}

int main() {
	init();
	cin >> a >> b;
	if(a == 2) {
		bfs(1);
		if(dst[1].count(a)) {
			if(cnt[1][a] > 1) {
				printf("Poor Benny\n");
			}
			else {
				vector<long long> path = fetch(1,b,2);
				for(int i = 0 ; i+1 < path.size() ; i++)
					printf("%lld->",path[i]);
				printf("%lld\n",b);
			}
		}
		else {
			printf("Unlucky Benny\n");
		}
	}
	else {
		solve();
	}
	return 0;
}