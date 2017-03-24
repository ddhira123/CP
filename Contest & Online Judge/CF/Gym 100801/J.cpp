#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

const int N = 1e5 + 5;
const int INF = 2e9 + 5;

pair<int,int> card[N];
int dp[N];
int tim[N];
int n, t;

int DP(int rng) {
	dp[n] = 0;
	deque<int> dq;
	dq.push_front(n);

	for(int i = n-1 ; i >= 1 ; i--) {
		while(dq.front() - i > rng) dq.pop_front();
		dp[i] = min(INF, tim[i] + dp[dq.front()]);

		//printf("%d -> dp %d jmp %d %d\n", i, dp[i], dq.front(), dp[dq.front()]);
		while(!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back(); 
		dq.push_back(i);
	}

	return dp[1];
}

int main() {
	OPEN("journey");
	scanf("%d %d",&n,&t);
	t -= (n-1);
	
	for(int i = 1 ; i < n ; i++) {
		scanf("%d",&card[i].first);
		card[i].second = i;
	}
	for(int i = 2 ; i < n ; i++)
		scanf("%d", tim + i);

	sort(card + 1, card + n);
	for(int i = 2 ; i < n ; i++)
		card[i].second = max(card[i].second, card[i-1].second);

	int lo = 1, hi = n-1;
	while(lo < hi) {
		int mid = (lo + hi) / 2;

		//printf("%d %d %d %d\n", mid, card[mid].first, card[mid].second, DP(card[mid].second));
		if(DP(card[mid].second) > t)
			lo = mid+1;
		else
			hi = mid;
	}

	printf("%d\n", card[lo].first);
	CLOSE();
	return 0;
}