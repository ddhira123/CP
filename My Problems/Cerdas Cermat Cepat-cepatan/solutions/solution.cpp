#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

vector<int> factors;
vector<int> dp;

int getId(int x) {
	return lower_bound(factors.begin(), factors.end(), x) - factors.begin();
}

void generateFactors(int x) {
	vector<int> revFactors;

	for(int i = 2 ; i*i <= x ; i++)
		if(x % i == 0) {
			factors.push_back(i);
			if(i*i != x) {
				revFactors.push_back(x / i);
			}
		}

	reverse(revFactors.begin(), revFactors.end());
	factors.insert(factors.end(), revFactors.begin(), revFactors.end());
	factors.push_back(x);
}

int solve(int x) {
	int idx = getId(x);
	int &ret = dp[idx];

	if(ret != -1) {
		return ret;
	}

	ret = 0;
	bool isPrime = 1;
	for(int i = 2 ; i*i <= x ; i++)
		if(x % i == 0) {
			isPrime = 0;

			int j = x / i;
			if(i != j) {
				ret = (ret + 1ll * solve(i) * solve(j)) % MOD;
			} else {
				long long same = solve(i);
				long long diff = same * (same-1) / 2;
				ret = (ret + same + diff) % MOD;
			}
		}

	if(isPrime) {
		ret = 1;
	}

	return ret;
}

int calc(int x) {
	generateFactors(x);
	dp = vector<int>(factors.size(), -1);

	return solve(x);
}

int main() {
	int x;
	cin >> x;
	cout << calc(x) << "\n";
	return 0;
}