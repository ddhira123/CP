#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second
#define pb push_back

int arr[55];
int n;

int main() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) cin >> arr[i];
	bool ok = 0;
	for(int i = 0 ; i < n ; i++)
		for(int j = i + 1 ; j < n ; j++)
			for(int k = j + 1 ; k < n ; k++) {
				int a[3] = {arr[i],arr[j],arr[k]};
				sort(a,a + 3);

				ok |= (a[0] != a[1] && a[1] != a[2] && a[2] - a[0] <= 2);
			}

	printf("%s\n",ok ? "YES" : "NO");		
	return 0;
}