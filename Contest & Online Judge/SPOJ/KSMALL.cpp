    #include <cstdio>
    #include <cstdlib>
    #include <algorithm>
    #include <vector>
    using namespace std;
    #define maxx 10000000
    typedef unsigned int ui;
    ui a,b,mod,arr[5000005],k,siz[maxx+5],y;
    vector<ui> bucket[5005];


    inline void gen(){
    if(mod>maxx)
    for(int i=0;i<5000000;i++){
    a = 31014 * (a & 65535) + (a >> 16);
    b = 17508 * (b & 65535) + (b >> 16);
    arr[i] = ((a << 16) + b)%mod;
    bucket[arr[i]/y].push_back(arr[i]);
    }
    else
    for(int i=0;i<5000000;i++){
    a = 31014 * (a & 65535) + (a >> 16);
    b = 17508 * (b & 65535) + (b >> 16);
    arr[i] = ((a << 16) + b)%mod;
    //if(arr[i]>=mod) arr[i]%=mod;
    siz[arr[i]]++;
    }
    }

    int main(){
    scanf("%u %u %u %u",&a,&b,&mod,&k);
    //puts("ganteng");
    y=mod/5000;
    gen();
    //puts("ayaz");
    //sort(arr,arr+5000000);
    if(mod<=maxx)
    for(int i=0;i<=maxx;i++)
    if(k>siz[i]) k-=siz[i];
    else{
    printf("%d\n",i);
    break;
    }
    else
    for(int i=0;i<5005;i++)
    if(k>bucket[i].size())
    k-=bucket[i].size();
    else{
    /*for(int j=0;j<bucket[i].size();j++)
    arr[j]=bucket[i][j];
    quick_sort(arr,0,bucket[i].size()-1,k);*/
    nth_element(bucket[i].begin(),bucket[i].begin()+k-1,bucket[i].end());
    printf("%u\n",bucket[i][k-1]);
    break;
    }
    return 0;
    }