#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

vector<int> stek;
int arr[N];
int n;
bool kiri[N],kanan[N];

int main(){
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++)
        scanf("%d",&arr[i]);
    for(int i = 0 ; i < n ; i++){
        while(!stek.empty() && stek.back() <= arr[i]) stek.pop_back();
        if(stek.empty()) kiri[i] = 1;
        stek.push_back(arr[i]);
    }   
    stek.clear();
    for(int i = n - 1 ; i >= 0 ; i--){
        while(!stek.empty() && stek.back() > arr[i]) stek.pop_back();
        if(stek.empty()) kanan[i] = 1;
        stek.push_back(arr[i]); 
    }
    int ans = 0;
    for(int i = 0 ; i < n ; i++)
        if(kiri[i] && kanan[i])
            ans++;
    cout << ans << endl;        
    return 0;
}

