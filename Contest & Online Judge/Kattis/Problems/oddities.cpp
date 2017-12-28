#include <bits/stdc++.h>
using namespace std;

int main(){
    int tc;
    cin >> tc;
    while(tc--){
    int n;
        cin >> n;
        cout << n << " is ";
        if(n % 2 == 0) cout << "even\n";
        else cout <<"odd\n";
    }
    return 0;
}

