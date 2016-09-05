#include <bits/stdc++.h>
using namespace std;

const int N = (int)5e5 + 6;

int n;
string s;
int a,b,t;

int main() {
	ios_base::sync_with_stdio(0);
	cin >> n >> a >> b >> t;
	cin >> s;
	int ans = 0;
	for(int times = 0 ; times < 2 ; times++) {
		int total_time = 0;

		for(int i = 0 ; i < n ; i++) {
			//cout << "time " << total_time << "\n";
			total_time += b * ('h' != s[i]);
			total_time++;

			if(total_time <= t) {
				//cout << "upd " << i + 1 << endl;
				ans = max(ans,i + 1);
			}

			total_time += a;
		}

		total_time -= a;

		int pos[256];
		int sum[256];
		int orie[256];
		pos['h'] = pos['w'] = n - 1;
		sum['h'] = sum['w'] = 0;
		orie['h'] = 'h';
		orie['w'] = 'w';
		char ori = 'h';

		for(int i = n - 1 ; i > 0 ; i--) {
			total_time -= a;
			total_time -= b * (s[i] != 'h');
			total_time--;

			int dummy = total_time + a * (i - 1);
			int last = sum[ori];

			//cout << dummy << "\n";
			while(pos[ori] > i - 1 && sum[ori] + dummy <= t) {
				sum[ori] += b * ('h' != s[pos[ori]]);
				sum[ori] += a;
				sum[ori]++;

				//cout << i << " " << pos[ori] << " " << sum[ori] << "\n";

				pos[ori]--;
			}

			if(last + dummy <= t) {
				//cout << "cur " << i << " " << pos[ori] << endl;
				ans = max(ans,i + n - pos[ori] - 2);
			}
		}

		s += s[0];
		reverse(s.begin(),s.end());
	}

	cout << ans << "\n";
	return 0;
}