#include <bits/stdc++.h>
using namespace std;

const int N = 1234567;

char s[N + 5];
int arr[N + 5];
int temp[N + 5];
int len;

void move(int x) {
	for(int i = 0 ; i < len ; i++) {
		int nex = i + x;
		if(nex >= len) nex -= len;
		temp[i] = arr[i] ^ arr[nex];
	}
}

bool finish(int x) {
	move(x);
	bool ok = 1;
	for(int i = 0 ; i < len && ok ; i++)
		ok &= (temp[i] == 0);
	return ok;
}

int main() {
	scanf("%s",s);
	len = strlen(s);

	int tot = 0;
	for(int i = 0 ; i < len ; i++) {
		if(s[i] == 'N') arr[i] = 0;
		else if(s[i] == 'R') arr[i] = 1;
		else if(s[i] == 'G') arr[i] = 2;
		else arr[i] = 3;

		tot += arr[i];
	}

	if(tot == 0) {
		puts("0");
		return 0;
	}

	int lim = 1;
	while(len % lim == 0) lim <<= 1;
	lim >>= 1;

	int ans = 0;
	for(; lim > 0 ; lim >>= 1) {
		if(!finish(lim)) {
			for(int i = 0 ; i < len ; i++)
				arr[i] = temp[i];
			ans += lim;
		}
	}

	if(finish(1))
		printf("%d\n",ans + 1);
	else
		puts("Party!");
	return 0;
}