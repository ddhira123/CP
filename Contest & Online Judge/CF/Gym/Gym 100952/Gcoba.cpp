#include <bits/stdc++.h>
using namespace std;

int n;
int depth[20];

bool stop() {
	for(int i = 1 ; i <= n ; i++)
		if(depth[i] == 0) return 0;
	return 1;
}

int rec(int dpt) {
	if(stop()) return 1;
	int win = 0;
	for(int i = 1 ; i <= n && !win ; i++)
		if(depth[i] == 0) {
			for(int j = 1 ; j <= i ; j++)
				if(depth[j] == 0 && i % j == 0)
					depth[j] = dpt;

			win |= !rec(dpt+1);

			for(int j = 1 ; j <= i ; j++)
				if(depth[j] == dpt && i % j == 0)
					depth[j] = 0;
		}

	return win;	
}

int main() {
	for(n = 2 ; n < 20 ; n++) {
		printf("%d %s\n",n,rec(1) ? "alice" : "bob");
	}
	return 0;
}