#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
pair<pair<int,int>, int> arr[N];
string s[N];
int n;

void read() {
	cin >> n;
	for(int i = 1 ; i <= n ; i++) {
		cin >> s[i];
	}
}

void preprocess() {
	for(int i = 1 ; i <= n ; i++) {
		int mins = 0;
		int sum = 0;
		for(char x : s[i]) {
			if(x == '(') sum++;
			else sum--;
			mins = min(mins, sum);
		}

		arr[i].first = {-mins, sum};
		arr[i].second = i;

		// printf("%d -> %d %d\n", i, -mins, sum);
	}

	sort(arr+1, arr+n+1);
	// for(int i = 1 ; i <= n ; i++)
		// printf("mins %d sum %d idx %d\n", arr[i].first.first, arr[i].first.second, arr[i].second);
}

bool cmp(pair<int,pair<int, int>> a, pair<int,pair<int, int>> b) {
	return a.first + a.second.first > b.first + b.second.first;
}

void work() {
	priority_queue<pair<int,pair<int, int>>> pq;
	vector<int> ans;

	int sum = 0;
	for(int i = 0 ; i <= n || !pq.empty() ; ) {
		int j = i+1;
		while(j <= n && arr[j].first.first <= sum) {
			pq.push({arr[j].first.second, {arr[j].first.first,arr[j].second}});
			j++;
		}

		// printf("%d %d\n", (int)pq.size(), i);
		if(pq.empty()) {
			break;
		}
		pair<int,pair<int, int>> cur = pq.top();
		pq.pop();
		if(cur.first < 0) {
			pq.push(cur);
			break;
		} else {
			sum += cur.first;
			ans.push_back(cur.second.second);
			i = j-1;
		}
	}

	if(pq.size() + ans.size() != n) {
		puts("NO");
	} else {
		vector<pair<int,pair<int, int>>> v;
		while(!pq.empty()) {
			pair<int,pair<int, int>> cur = pq.top();
			pq.pop();

			swap(cur.first, cur.second.first);
			v.push_back(cur);
		}
		sort(v.begin(), v.end(), cmp);
		// reverse(v.begin(), v.end());

		for(pair<int,pair<int, int>> x : v) {
			int mins = x.first;
			int add = x.second.first;

			if(sum < mins) {
				break;
			}

			sum += add;
			ans.push_back(x.second.second);
		}

		if(ans.size() == n && sum == 0) {
			puts("YES");
			for(int x : ans) printf("%d ", x);
			puts("");
		} else {
			puts("NO");
		}
	}
}

int main() {
	read();
	preprocess();
	work();
	return 0;
}