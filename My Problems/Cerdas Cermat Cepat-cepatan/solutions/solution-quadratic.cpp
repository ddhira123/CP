#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

vector<int> factors;
vector<int> dp;

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

int calc(int x) {
	generateFactors(x);
	dp = vector<int>(factors.size(), 0);

	for(int i = 0 ; i < factors.size() ; i++) {
		bool isPrime = 1;
		int &ret = dp[i];

		ret = 0;
		int k = i-1;
		for(int j = 0 ; j < i ; j++)
			if(factors[i] % factors[j] == 0) {
				isPrime = 0;
				int x = factors[i] / factors[j];

				while(x != factors[k]) {
					k--;
				}

				if(k < j) {
					break;
				}
				else if(k == j) {
					long long add = 1ll * (dp[j]+1) * dp[j] / 2;
					ret = (ret + add) % MOD;
				} else {
					long long add = 1ll * dp[j] * dp[k];
					ret = (ret + add) % MOD;
				}
			}

		if(isPrime)
			ret = 1;

		assert(ret != 0);
	}

	return dp.back();
}

int main() {
	int x;
	cin >> x;
	cout << calc(x) << "\n";
	return 0;
}