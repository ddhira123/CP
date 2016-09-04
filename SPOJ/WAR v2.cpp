#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int M = 8005;
const double EPS = 1e-9;
double PI = acos(-1);

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

struct point {
	int x;
	int y;
	
	bool operator <(point other) const {
		if(x == other.x) {
			return y < other.y;
		}
		return x < other.x;
	}
	
	bool operator ==(point other) const {
		return x == other.x && y == other.y;
	}
};

LL crossProduct(point origin,point p,point q) {
	return (LL)(p.x - origin.x) * (LL)(q.y - origin.y) - (LL)(q.x - origin.x) * (LL)(p.y - origin.y);
}

LL dotProduct(point origin,point p,point q) {
	return (LL)(p.x - origin.x) * (LL)(q.x - origin.x) + (LL)(q.y - origin.y) * (LL)(p.y - origin.y);
}

double vectorLength(LL dx,LL dy) {
	return sqrt(dx * dx + dy * dy);
}

bool ccw(point origin,point p,point q) {
	return crossProduct(origin,p,q) > 0;
}

double angle(point origin,point p,point q) {
	double res = dotProduct(origin,p,q);
	double a = vectorLength(p.x - origin.x,p.y - origin.y);
	double b = vectorLength(q.x - origin.x,q.y - origin.y);
	
	return acos(res / (a * b));
}

struct polygon{
	vector<point> node;
	LL area;
	
	polygon() {
		node.clear();
		area = 0;
	}
	
	bool isInside(point x) {
		double sum = 0;
		for (int i = 0; i < (int)node.size()-1; i++) {
			double add;
			if (ccw(x, node[i], node[i+1]))
				add = angle(x, node[i], node[i+1]);
			else 
				add = -angle(x, node[i], node[i+1]); 
			
			sum += add;
			//printf("%.5lf\n",add);	
		}
		return fabs(fabs(sum) - 2*PI) < EPS; 
	}		
	
	void calcArea() {
		area = 0;
		for(int i = 0 ; i < (int)node.size() - 1 ; i++) {
			LL xa = node[i].x, ya = node[i].y;
			LL xb = node[i + 1].x, yb = node[i + 1].y;
			area = area + (xa * yb) - (ya * xb);
		}
		//printf("%lld\n",area);
		area = abs(area);
	}
	
	void init() {
		calcArea();	
	}
	
	void print() {
		for(point x : node)
			printf("%d %d\n",x.x,x.y);
	}
};

point pivot;
vector<point> v;
vector<int> adj[2 * M];

vector<int> border[M]; // sharing border
vector<pair<double,int > > adjD[M]; // to sort neighbor, by CW / CCW
point capital[N]; // list of capital
point pointOfLine[M][2]; // for input
pii line[M]; // edgelist
vector<int> ans[N]; // holding answer
polygon poly[N]; // polygon which contain i-th capital
set<pii> see; // to ensure each edge traveled at most twice, with different direction
vector<polygon> allPolygon; // list of all polygon, may contain same polygon with different traversal direction
vector<pair<LL,int> > calon[N]; // list of smallest containing polygon
bool used[M * 10]; // to check if there is a capital which is contained in i-th polygon
int pake[N]; // ID of polygon which contains i-th capital
int matched[N]; // number of shared border
int sial[N]; // ID of polygon which contains polygon which contains i-th capital
int n,m;

int getPointIndex(point &x) {
	return lower_bound(v.begin(),v.end(),x) - v.begin();
}

int getLineIndex(pii &x) {
	return lower_bound(line,line + m,x) - line;
}

void makeUnique(vector<int> &x) {
	sort(x.begin(),x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
}

void makeUnique(vector<point> &x) {
	sort(x.begin(),x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
}

void reset() {
	for(int i = 0 ; i < allPolygon.size() ; i++)
		used[i] = 0;
	allPolygon.clear();
	see.clear();
	for(int i = 0 ; i < v.size() ; i++) {
		adj[i].clear();
		adjD[i].clear();
	}
	v.clear();
	for(int i = 0 ; i < m ; i++) {
		border[i].clear();
	}
	for(int i = 0 ; i < n ; i++) {
		ans[i].clear();
		matched[i] = 0;
	}
}

bool readInput() {
	scanf("%d %d",&n,&m);
	
	for(int i = 0 ; i < n ; i++) {
		scanf("%d %d",&capital[i].x,&capital[i].y);
	}
	
	for(int i = 0 ; i < m ; i++) {
		for(int j = 0 ; j < 2 ; j++) {
			scanf("%d %d",&pointOfLine[i][j].x,&pointOfLine[i][j].y);
			v.pb(pointOfLine[i][j]);
		}
	}
	
	return (n | m);
}

void convertToGraph() {
	makeUnique(v);
	
	for(int i = 0 ; i < m ; i++) {
		line[i].fi = getPointIndex(pointOfLine[i][0]);
		line[i].se = getPointIndex(pointOfLine[i][1]);
		
		adj[line[i].fi].pb(line[i].se);
		adj[line[i].se].pb(line[i].fi);
		
		if(line[i].fi > line[i].se) {
			swap(line[i].fi,line[i].se);
		}
	}
	
	sort(line,line + m);
	
	for(int i = 0 ; i < v.size() ; i++) {
		makeUnique(adj[i]);
		vector<pair<double,int> > lol;
		
		for(int x : adj[i]) {
			point haha = v[x];
			haha.x -= v[i].x;
			haha.y -= v[i].y;
			lol.pb({atan2(haha.y,haha.x),x});
		}

		sort(lol.begin(),lol.end());
		adjD[i] = lol;
	}
}

void traverse(int prv,int now) {
	polygon res;
	set<pii> seen;
	
	while(!see.count({prv,now})) {
		res.node.pb(v[now]);
		pii temp = {prv,now};
		see.insert(temp);
		
		int haha = 0;
		double ang = atan2(v[prv].y - v[now].y, v[prv].x - v[now].x);
		
		int lo = 0;
		int hi = adj[now].size() - 1;
		
		pair<double,int> yay = {ang,prv};
		haha = lower_bound(adjD[now].begin(),adjD[now].end(),yay) - adjD[now].begin();
		
		assert(adjD[now][haha].second == prv);
		
		haha--;
		if(haha == -1) haha = (int)adjD[now].size() - 1;
		
		prv = now;
		now = adjD[now][haha].second;
		//printf("idx %d prv %d now %d\n",idx,prv,now);		
	}
	
	if(!res.node.empty()) {
		res.node.pb(res.node[0]);
		res.init();
		allPolygon.pb(res);
	}
}

void solve() {
	for(int i = 0 ; i < v.size() ; i++)
		for(int j : adj[i])
			traverse(i,j);
	
	for(int i = 0 ; i < n ; i++) {
		priority_queue<pair<LL,int> > pq;
		for(int j = 0 ; j < allPolygon.size() ; j++) {
			if(allPolygon[j].isInside(capital[i])) {
				pq.push({allPolygon[j].area,j});
				if(pq.size() > 100) pq.pop(); 
			}
		}	
		vector<pair<LL,int> > luar;
		while(!pq.empty()) {
			auto temp = pq.top();
			pq.pop();
			temp.fi = temp.fi;
			luar.pb(temp);
		}
		pake[i] = luar.back().se;
		poly[i] = allPolygon[pake[i]];
		used[luar.back().se] = 1;
		luar.pop_back();
		calon[i] = luar;
	}
	
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j + 1 < poly[i].node.size() ; j++) {
			point a = poly[i].node[j];
			point b = poly[i].node[j + 1];
			
			int aa = getPointIndex(a);
			int bb = getPointIndex(b);
			
			if(aa > bb) swap(aa,bb);
			
			pii temp = {aa,bb};
			int id = getLineIndex(temp);
			assert(line[id] == temp);
			border[id].push_back(i); 
		}
	}
	
	for(int i = 0 ; i < m ; i++) {
		makeUnique(border[i]);
		
		assert(border[i].size() <= 2);
		
		for(int j = 0 ; j < border[i].size() ; j++)
			for(int k = j + 1 ; k < border[i].size() ; k++) {
				int a = border[i][j];
				int b = border[i][k];
				ans[a].pb(b);
				ans[b].pb(a);
				matched[a]++;
				matched[b]++;
			}
	}
	
	for(int i = 0 ; i < n ; i++)
		if(matched[i] < (int)poly[i].node.size() - 1) {
			sial[i] = -1;
			while(!calon[i].empty() && !used[calon[i].back().se]) calon[i].pop_back();
			if(!calon[i].empty()) {
				sial[i] = calon[i].back().se;
				calon[i].clear();
			}
			for(int j = 0 ; j < n ; j++)
				if(pake[j] == sial[i]) {
					ans[i].pb(j);
					ans[j].pb(i);
				}
		}		
	for(int i = 0 ; i < n ; i++) {
		makeUnique(ans[i]);
		printf("%d",(int)ans[i].size());
		for(int x : ans[i]) {
			printf(" %d",x + 1);
		}
		puts("");
	}
}

int main() {
	while(readInput()) {
		convertToGraph();
		solve();
		reset();
	}
	return 0;
}
