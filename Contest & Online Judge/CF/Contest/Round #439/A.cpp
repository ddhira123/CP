#include <bits/stdc++.h>
using namespace std;

int main() {
	int k; cin >> k;
	int butuh = 0;
	int x = k;
	if(k == 0) {
		puts("a");
		return 0;
	}
	while(x > 0) {
		butuh++;
		int j = 1;
		while(j * (j - 1) / 2 <= x) j++;
		j--;
		for(int i = 0 ; i < j ; i++) {
			printf("%c", butuh + 'a' - 1);
		}
		x -= j * (j - 1) / 2;
	}
	assert(butuh <= 26);
	puts("");
	return 0;
}