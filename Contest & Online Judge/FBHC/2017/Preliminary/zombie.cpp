#include <bits/stdc++.h>
using namespace std;

const int MAX_X = 20;
const int MAX_Y = 20;

struct data {
	int x;
	int y;
	int z;
};

long double dp[MAX_Y+5][MAX_X+5][MAX_Y*MAX_X+5];

void precompute() {
	for(int sides = 1 ; sides <= MAX_Y ; sides++) {
		dp[sides][0][0] = 1;
		long double mul = 1.0 / sides;
		for(int trial = 1 ; trial <= MAX_X ; trial++) {
			for(int sum = trial ; sum <= MAX_Y * MAX_X ; sum++)
				for(int sides_used = 1 ; sides_used <= min(sum, sides) ; sides_used++) {
					dp[sides][trial][sum] += mul * dp[sides][trial-1][sum-sides_used];
				}
		}

		for(int trial = 1 ; trial <= MAX_X ; trial++)
			for(int sum = MAX_X * MAX_Y ; sum >= 0 ; sum--)
				dp[sides][trial][sum] += dp[sides][trial][sum+1];
	}
}

data parse(string str) {
	bool hasNegative = 0;
	bool hasPositive = 0;
	vector<int> v;
	int val = 0;

	for(char x : str) {
		if(x == 'd') {
			v.push_back(val);
			val = 0;
		}
		else if(x == '+') {
			v.push_back(val);
			val = 0;
			hasPositive = 1;
		}
		else if (x == '-') {
			v.push_back(val);
			val = 0;
			hasNegative = 1;
		}
		else {
			val = 10 * val + (x - '0');
		}
	}

	if(hasNegative) {
		v.push_back(-val);
	}
	else {
		v.push_back(val);
	}

	data ret;
	ret.x = v[0];
	ret.y = v[1];
	ret.z = v.size() == 3 ? v[2] : 0;

	return ret;
}

int main() {
	precompute();
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int h, s;
		cin >> h >> s;

		long double ret = 0;
		for(int i = 0 ; i < s ; i++) {
			string str;
			cin >> str;
			data dat = parse(str);

			int curH = h - dat.z;
			curH = max(curH, 0);

			long double val = 0;
			if(curH <= MAX_X * MAX_Y)
				val = dp[dat.y][dat.x][curH];

			ret = max(ret, val);
		}

		cout << "Case #" << tc << ": " << fixed << setprecision(8) << ret << "\n";
	}
	return 0;
}