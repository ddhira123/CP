#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
const int N = 100005;

bool isEqual(double a,double b) {
	return fabs(a - b) < EPS;
}

bool isHigher(double a,double b) {
	return a > b + EPS;
}

struct Line {
	double xa;
	double ya;
	double xb;
	double yb;
};

struct Event {
	double x;
	double ya;
	double yb;
	int type; // 0: tambah 1: query 2: remove

	bool operator <(Event other) const {
		if(isEqual(x,other.x))
			return type < other.type;
		return isHigher(other.x,x);
	}
};

vector<double> uniq;
vector<Event> events;
int BIT[4 * N];

// vertikal
Line red[N];
// horizontal
Line blue[N];

int n;

void update(int x,int val) {
	for(; x <= uniq.size() ; x += x & -x)
		BIT[x] += val;
}

int query(int x) {
	int ret = 0;

	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}

	return ret;
}

void makeUniq() {
	sort(uniq.begin(),uniq.end());
	vector<double> temp;

	for(int i = 0 ; i < uniq.size() ;) {
		temp.push_back(uniq[i]);

		int j = i;
		while(j < uniq.size() && isEqual(uniq[i],uniq[j]))
			j++;

		i = j;
	}

	uniq = temp;
}

// tribute to Aldi
int lowerGua(double x) {
	int lo = 0;
	int hi = uniq.size() - 1;

	while(lo < hi) {
		int mid = (lo + hi + 1) / 2;

		if(isHigher(uniq[mid],x))
			hi = mid - 1;
		else
			lo = mid;
	}

	return lo;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%lf %lf %lf",&blue[i].xa,&blue[i].xb,&blue[i].ya);
		
		if(isHigher(blue[i].xa,blue[i].xb)) {
			swap(blue[i].xa,blue[i].xb);
		}
	}
	for(int i = 1 ; i <= n ; i++) {
		scanf("%lf %lf %lf",&red[i].ya,&red[i].yb,&red[i].xa);

		if(isHigher(red[i].ya,red[i].yb))
			swap(red[i].ya,red[i].yb);
	}
}

void init() {
	// bikin uniq
	uniq.push_back(-1);
	for(int i = 1 ; i <= n ; i++)
		uniq.push_back(blue[i].ya);
	for(int i = 1 ; i <= n ; i++) {
		uniq.push_back(red[i].ya);
		uniq.push_back(red[i].yb);
	}
	makeUniq();

	// bikin events
	for(int i = 1 ; i <= n ; i++) {
		events.push_back((Event){blue[i].xa,blue[i].ya,blue[i].ya,0});
		events.push_back((Event){blue[i].xb,blue[i].ya,blue[i].ya,2});
	}
	for(int i = 1 ; i <= n ; i++) {
		events.push_back((Event){red[i].xa,red[i].ya,red[i].yb,1});
	}

	sort(events.begin(),events.end());
}

long long solve() {
	long long res = 0;

	for(Event x : events) {
		if(x.type == 0) {
			int id = lowerGua(x.ya);
			update(id,1);
		}
		else if(x.type == 2) {
			int id = lowerGua(x.ya);
			update(id,-1);
		}
		else {
			int ida = lowerGua(x.ya);
			int idb = lowerGua(x.yb);
			res += (query(idb) - query(ida - 1));
		}
	}

	return res;
}

int main() {
	read();
	init();
	printf("%lld\n",solve());
	return 0;
}