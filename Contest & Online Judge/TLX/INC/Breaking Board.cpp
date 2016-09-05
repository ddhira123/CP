#include <bits/stdc++.h>
using namespace std;

const int N = 105;

vector<int> uniqRow;
vector<int> uniqCol;
int all[N][N], onlyX[N][N];
int dp[N][N][N];
int coinR[N], coinC[N];
char tipe[N][5];
int r,c,n;

void makeUnique(vector<int> &v){
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
}

void init(){
	scanf("%d %d %d",&r,&c,&n);
	uniqRow.clear();
	uniqCol.clear();
	for(int i = 0 ; i < n ; i++){
		scanf("%d %d %s",&coinR[i], &coinC[i], tipe[i]);
		uniqRow.push_back(coinR[i]);
		uniqCol.push_back(coinC[i]);
		//uniqRow.push_back(coinR[i] - 1);
		//uniqCol.push_back(coinC[i] - 1);
	}	
	uniqRow.push_back(0);
	uniqCol.push_back(0);
	
	makeUnique(uniqRow);
	makeUnique(uniqCol);
	
	for(int i = 0 ; i < n ; i++){
		coinR[i] = lower_bound(uniqRow.begin(),uniqRow.end(),coinR[i]) - uniqRow.begin();
		coinC[i] = lower_bound(uniqCol.begin(),uniqCol.end(),coinC[i]) - uniqCol.begin();
	}
}

int solve(int row,int col,int sisa){
	if(row == uniqRow.size() || col == uniqCol.size() || sisa < 0)
		return (int)1e9;
	if(row == uniqRow.size() - 1 && col == uniqCol.size() - 1){
		if(sisa > 0) return (int)1e9;
		return 0;
	}	
	int &ret = dp[row][col][sisa];
	if(ret != -1) return ret;
	ret = (int)1e9;
	ret = min(ret,solve(row + 1,col,sisa));
	ret = min(ret,solve(row,col + 1,sisa - all[row][col + 1]) + onlyX[row][col + 1]);
	//cout << row << " " << col << " " << sisa << " " << ret << endl;
	return ret;
}

int DP(){
	int ans = (int)1e9;
	for(int iter = 0 ; iter < 2 ; iter++){
		int onlyO = 0;
		memset(all,0,sizeof all);
		memset(onlyX,0,sizeof onlyX);
		memset(dp,-1,sizeof dp);
		for(int i = 0 ; i < n ; i++){
			int row = coinR[i];
			int col = coinC[i];
			all[row][col]++;
			if(tipe[i][0] == 'X')
				onlyX[row][col]++;
			else
				onlyO++;	
		}
		for(int j = 0 ; j < uniqCol.size() ; j++)
			for(int i = 1 ; i < uniqRow.size() ; i++){
				all[i][j] += all[i - 1][j];
				onlyX[i][j] += onlyX[i - 1][j];
			}
		ans = min(ans,solve(0,0,onlyO));
		//cout << solve(0,0,onlyO) << endl;	
		for(int i = 0 ; i < n ; i++)
			tipe[i][0] = (tipe[i][0] == 'O' ? 'X' : 'O');
	}
	assert(ans != (int)1e9);
	return ans;
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		init();
		printf("Case #%d: %d\n",t,DP());
	}
	return 0;
}
