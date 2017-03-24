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

int main() {
	OPEN("alex");
	double w, h;
	cin >> w >> h;
	double ans = 0;

	ans = min(w / 2, h / 2);
	ans = max(ans, min(w, h / 3));
	ans = max(ans, min(h, w / 3));

	printf("%.10lf\n", ans);

	CLOSE();
	return 0;
}