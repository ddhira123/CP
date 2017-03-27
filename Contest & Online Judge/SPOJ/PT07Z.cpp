#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

stack<int> proses,sisa,pret;
vector<int> adj[50010];
bool cek[50010];
int a,b,c,d,e,maks,isi[50001];

int dfs(int posisi)
{int dum=0,k,i=posisi,g;
 for (k=0;k<adj[posisi].size();k++)
  if(cek[adj[posisi][k]])
   {cek[adj[posisi][k]]=false;
    g=1+dfs(adj[posisi][k]);
    if (g>dum)
     {i=adj[posisi][k];
      dum=g;
     }
    cek[adj[posisi][k]]=true;
   }
 isi[posisi]=isi[i];
 return dum;
}

void cari(int x)
{int j;
 for (j=1;j<=a;j++)
  isi[j]=j;
 cek[x]=false;
 j=1+dfs(x);
 cek[x]=true;
 if (j>maks)
  {maks=j;
   cari(isi[x]);
  }
}

int main()
{scanf("%d",&a);
 for (b=1;b<a;b++)
  {scanf("%d %d",&c,&d);
    cek[c]=cek[d]=true;
   adj[c].push_back(d);
   adj[d].push_back(c);
  }
  maks=0;
  cari(1);
 printf("%d\n",maks-1);
}