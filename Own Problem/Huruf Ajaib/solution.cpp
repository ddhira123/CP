#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const int LETTER = 26;
const LL INF = 4e18;

string s;
LL n, m, k, x;
LL total;

int nex[N][LETTER];
int lst[N];

bool ada;

void makeNex() {
	for(int i = 0 ; i < n ; i++) {
		memset(nex[i],-1,sizeof nex[i]);
	}
	memset(lst,-1,sizeof lst);

	for(int i = n-1 ; i >= 0 ; i--) {
		for(int j = 0 ; j < LETTER ; j++)
			nex[i][j] = lst[j];
		lst[s[i] - 'a'] = i;
	}

	for(int i = n-1 ; i >= 0 ; i--) {
		for(int j = 0 ; j < LETTER ; j++)
			if(nex[i][j] == -1)
				nex[i][j] = lst[j];
	}
}

LL getNext(LL idx,char ch) {
	LL pos = idx % n;
	if(nex[pos][ch-'a'] == -1) return INF;
	if(nex[pos][ch-'a'] > pos) return idx + nex[pos][ch-'a'] - pos;
	return idx + n - pos + nex[pos][ch-'a'];
}

char get(LL idx,LL urutan,LL sisa) {
	urutan--; sisa--;

	while(urutan > 0 && total-idx > sisa+1) {
		for(int i = 0 ; i < 26 ; i++) {
			LL nxt = getNext(idx,i+'a');
			if(total-nxt >= sisa) {
				idx = nxt;
				break;
			}
		}
		
		urutan--; sisa--;
	}

	return s[(idx + urutan) % n];
}

void init() {
	cin >> s;
	cin >> m >> k >> x;
	n = s.length();
	total = n*m;
}

int solve() {
	makeNex();

	int letter = -1;
	for(int i = 0 ; i < n ; i++) {
		if(letter == -1 || letter > s[i])
			letter = s[i]; 
	}

	vector<int> pos;
	for(int i = 0 ; i < n ; i++)
		if(s[i] == letter)
			pos.push_back(i);


	if((LL)pos.size() * m >= k) {
		return letter;
	}
	else if(total-pos[0] < k) {
		int mins = -1;
		for(int i = 0 ; total-i >= k ; i++)
			if(mins == -1 || s[mins] > s[i])
				mins = i;

		return get(mins,x,k);	
	}
	else {
		LL lo = 0, hi = (LL)pos.size()*m-1;

		while(lo < hi) {
			LL mid = (lo + hi + 1) / 2;
			LL loop = mid / pos.size();
			LL now = n * loop + pos[mid % pos.size()];

			if(mid + total-now >= k)
				lo = mid;
			else
				hi = mid-1;
		}

		if(lo+1 >= x)  {
			return letter;
		}	

		LL loop = lo / pos.size();
		LL now = n * loop + pos[lo % pos.size()];

		return get(now,x-lo,k-lo);
	}
}

int main() {
	int t; cin >> t;

	for(int tc = 1 ; tc <= t ; tc++) {
		init();
		cout << (char)solve() << "\n";
	}
	return 0;
}