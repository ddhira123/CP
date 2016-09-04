#include <cstdio>
#include <climits>
#include <queue>
using namespace std;

template<typename T>
T getNum()
{
	T res=0;
	char c;
	while(1) {
		c=getchar_unlocked();
		if(c==' ' || c=='\n') continue;
		else break;
	}
	res=c-'0';
	while(1) {
		c=getchar_unlocked();
		if(c>='0' && c<='9') res=10*res+c-'0';
		else break;
	}
	return res;
}

struct Vertex {
	Vertex *parent;
	int left, count, size;
};

Vertex verticles[3000001];

int nwd(int a, int b) {
	return b ? nwd(b, a%b) : a;
}

int T[3000001];

int main() {
	int n;
	n=getNum<int>();
	
	verticles[1].parent = NULL;
	for( int i = 2; i <= n; i++ ) {
		int p;
		p=getNum<int>();
		verticles[i].parent = verticles + p;
		verticles[p].count++;
	}

	queue<Vertex*> Q;
	for( int i = 1; i <= n; i++ ) {
		verticles[i].size = 1;
		verticles[i].left = verticles[i].count;
		if( verticles[i].count == 0 )
			Q.push( verticles+i );
	}

	while( !Q.empty() ) {
		Vertex* v = Q.front();
		Q.pop();
		if( v->parent ) {
			v->parent->size += v->size;
			if( v->parent->left-- == 1 )
				Q.push( v->parent );
			int val = nwd(v->size, n - v->size );
			for( int i = 1; i*i <= val; i++ ) {
				if( val % i == 0 ) {
					T[i]++;
					if( val/i > i )
						T[val/i]++;
				}
			}
		}
	}
	for( int i = 1; i <= n; i++ ) {
		if( n%i == 0 and T[n/i]+1 == i )
			printf("%d ", i );
	}
	printf("\n");
	return 0;
}
