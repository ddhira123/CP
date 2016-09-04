#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e7;
const int M = 151;

bool flag[N + 21];
int prime[700005];
int prima;
int ans[M][M];
int nex[M][M];
int prv[M][M];

void sieve() {
	memset(flag,1,sizeof flag);
	prima = 0;
	flag[0] = flag[1] = 0;
	for(int i = 2 ; i <= N + 20 ; i++)
		if(flag[i]) {
			prime[prima++] = i;
			//cout << prima << " " << i << endl;
			int k = (N + 20) / i;
			if(i <= k)
				for(int j = i * i ; j <= N + 20 ; j += i)
					flag[j] = 0;
		}
	cout << prima << endl;	
}

void precompute() {
	memset(ans,-1,sizeof ans);
	int haha = 0;
	int tot = 0;
	cout << prime[2186] << " " << prime[2188] << endl;
	for(int i = 0 ; prime[i] <= N ; i++)
		if(prime[i] >= M) 
			for(int j = i ; prime[j] <= N && j - i + 1 < M && prime[j] - prime[i] + 1 < M ; j++) {
				cout << i << " " << j << " " << prime[i] << " " << prime[j] << endl;
				//getchar();
				int kiri = prime[i - 1];
				int kanan = prime[j + 1];
				if(kiri < M) kiri = prime[i];
				if(kanan > N) kanan = prime[j];

				int bawah = prime[j] - prime[i] + 1;
				int atas = bawah + prime[i] - kiri + kanan - prime[j];
				atas = min(atas,M - 1);

				for(int i = bawah ; i <= atas ; i++) {
					ans[j - i + 1][i] = 1;
				}
			}

	cout << tot << endl;
}

int k,l,m;

bool isMagic(int x) {
	return x <= m || !flag[x];
}

int small() {
	int tot = 0;
	int ans = -1;
	for(int i = 1 ; i <= k ; i++)
		tot += isMagic(i);
	if(tot == l) ans = 1;
	for(int i = 2 ; i < M ; i++) {
		tot -= isMagic(i - 1);
		tot += isMagic(i + k - 1);
		if(tot == l) ans = max(ans,i);
	}
	return ans;

}

int main() {
	sieve();
	precompute();

	return 0;
}