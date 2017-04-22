#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> can;
bool active[N];
int n, k, r;

int main() {
	cin >> n >> k >> r;
	for(int i = 0 ; i < k ; i++) {
		int x; cin >> x;
		active[x] = 1;
	}

	int sum = 0;
	for(int i = 1 ; i <= r ; i++) {
		if(active[i]) {
			sum++;
		} else {
			can.push_back(i);
		}
	}

	int ret = 0;
	while(sum < 2) {
		active[can.back()] = 1;
		can.pop_back();

		ret++;
		sum++;
	}

	for(int i = r+1 ; i <= n ; i++) {
		sum += active[i];
		if(!active[i]) {
			can.push_back(i);
		}
		sum -= active[i-r];

		if(sum < 2) {
			active[can.back()] = 1;
			can.pop_back();

			ret++;
			sum++;
		}
	}

	cout << ret << endl;
	return 0;
}