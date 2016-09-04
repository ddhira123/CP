#include <bits/stdc++.h>
using namespace std;

const int N=10;

void r(){
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			printf("n>=%d?r(%d,%d):g();\n",max(i,j),i,j);
}

void o(int i,int j,int k) {
	printf("a[%d][%d]=(a[%d][%d]<=a[%d][%d]+a[%d][%d]?a[%d][%d]:a[%d][%d]+a[%d][%d]);\n",
		j,k,j,k,j,i,i,k,j,k,j,i,i,k);	
}

void flloyd(){
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			for(int k=1;k<=N;k++)
				printf("n>=%d?o(%d,%d,%d):g();\n",max(i,max(j,k)),i,j,k);
}

void solve(){
	printf("m=0;\n");
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)	
			printf("n>=%d?(m=m>=a[%d][%d]?m:a[%d][%d]):n=n;\n",max(i,j),i,j,i,j);			
}

int main(){
	printf("#include<bits/stdc++.h>\nusing namespace std;\nint a[15][15];\nint n;\nint m;\n");
	printf("void r(int x,int y){cin>>a[x][y];}\nvoid g(){}\n");
	printf("int main(){\n");
	printf("cin>>n;\n");
	r();
	flloyd();
	solve();
	printf("cout<<m<<endl;\nreturn 0;\n}\n");
	return 0;
}