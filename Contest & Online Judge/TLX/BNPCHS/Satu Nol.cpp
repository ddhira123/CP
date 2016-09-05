#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int tc;
	cin >> tc;
	for(int t = 1 ; t <= tc ; t++){
		int n;
		cin >> n;
		int mins[2] = {1000000000,1000000000};
		int maks[2] = {-1000000000,-1000000000};
		for(int i = 0 ; i < n ; i++){
			int x,y;
			cin >> x >> y;
			int ret = x - y;
			mins[0] = min(mins[0],ret);
			maks[0] = max(maks[0],ret);
			
			ret = x + y;
			mins[1] = min(mins[1],ret);
			maks[1] = max(maks[1],ret);			
		}
		int ans = max(maks[0] - mins[0], maks[1] - mins[1]);
		cout << "Kasus #" << t << ": " << ans << endl;
	}
	return 0;
}
