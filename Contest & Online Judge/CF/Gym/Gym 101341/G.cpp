#include <bits/stdc++.h>
using namespace std;

char dummy[30];

string readString() {
	scanf("%s", dummy);
	return (string)dummy;
}

const int N = 2e5 + 5;

pair<int, string> ans[N];
int n, m;

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++) {
		ans[i].second = readString();
		ans[i].first = 0;
	}

	scanf("%d", &m);
	for(int i = 0 ; i < m ; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		ans[a] = ans[b];
		ans[a].first++;
	}

	for(int i = 0 ; i < ans[1].first ; i++)
		printf("I_love_");
	printf("%s\n", ans[1].second.c_str());
	return 0;
}