#include <bits/stdc++.h>
using namespace std;

const int N = 50000 + 5;

int arr[N];
int n;

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
}

set<int> st;

int main() {
	read();
	for(int i = 1 ; i <= n ; i++)
		st.insert(arr[i]);
	while(1) {
		auto it = st.end();
		it--;
		int x = *it;
		int tx = x;
		x /= 2;
		while(st.count(x)) x /= 2;
		if(x != 0) {
			st.erase(tx);
			st.insert(x);
		}
		else {
			break;
		}
	}
	for(auto it : st)
		printf("%d\n",it);
	return 0;
}