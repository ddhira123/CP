#include <bits/stdc++.h>
using namespace std;

const int MX = 304;

bool flag[31][6][8][MX][MX];

int dr[8] = {-1,-1,0,1,1,1,0,-1};
int dc[8] = {0,1,1,1,0,-1,-1,-1};
int n;

int arr[35];

struct data {
	int num;
	int step;
	int dir;
	int row;
	int col;

	bool isSet() {
		return flag[num][step][dir][row][col];
	}

	void set() {
		flag[num][step][dir][row][col] = 1;
	}

	void print() {
		printf("%d %d %d %d %d\n",num,step,dir,row,col);
	}
};

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++)
		scanf("%d",&arr[i]);
}

void bfs() {
	queue<data> q;
	q.push((data){0,arr[0],0,MX/2,MX/2});
	flag[0][arr[0]][0][MX/2][MX/2] = 1;

	while(!q.empty()) {
		data now = q.front();
		q.pop();
		//now.print();
		if(now.num == n-1 && now.step == 1) continue;
		if(now.step == 1) {
			for(int i = -1 ; i <= 1 ; i += 2) {
				data nextData;
				nextData.num = now.num+1;
				nextData.step = arr[nextData.num];
				nextData.dir = (now.dir + i + 8) % 8;
				nextData.row = now.row + dr[nextData.dir];
				nextData.col = now.col + dc[nextData.dir];

				if(nextData.isSet()) continue;
				nextData.set();
				q.push(nextData);
			}
		}
		else {
			data nextData = now;
			nextData.step--;
			nextData.row = now.row + dr[nextData.dir];
			nextData.col = now.col + dc[nextData.dir];

			if(nextData.isSet()) continue;
			nextData.set();
			q.push(nextData);
		}
	}
	//puts("done");
}

int countAll() {
	int ans = 0;
	for(int i = 0 ; i < MX ; i++)
		for(int j = 0 ; j < MX ; j++) {
			bool ada = 0;
			for(int k = 0 ; k < n ; k++)
				for(int l = 0 ; l < 6 ; l++)
					for(int it = 0 ; it < 8 ; it++)
						ada |= flag[k][l][it][i][j];
			ans += ada;		
		}
	return ans;			
}

int main() {
	read();
	bfs();
	printf("%d\n",countAll());
	return 0;
}