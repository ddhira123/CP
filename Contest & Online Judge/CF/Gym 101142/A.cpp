#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

int main() {
	OPEN("anniversary");
	int w, h, ax, ay, bx, by;
	cin >> w >> h >> ax >> ay >> bx >> by;
	if(ax != bx)
		printf("%d %d %d %d\n",min(ax,bx), 0, max(ax,bx), h);
	else
		printf("%d %d %d %d\n",0,min(ay,by), w, max(ay,by));
	CLOSE();
	return 0;
}