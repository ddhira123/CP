#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int arr[N];
bool udah[N];
int n;

void read() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> arr[i];
    }
}

bool solve() {
    for(int i = n ; i >= 1 ; i--) {
        if(i > 1)
            arr[i]--;

        for(int j = i+1 ; j <= n && arr[i] > 0 ; j++) {
            if(!udah[j]) {
                // cout << i << " " << j << endl;
                udah[j] = true;
                arr[i]--;
            }
        }

        if(arr[i]) {
            return false;
        }
    }

    for(int i = 1 ; i <= n ; i++) {
        // cout << i << " " << udah[i] << endl;
    }

    for(int i = 2 ; i <= n ; i++)
        if(!udah[i]) {
            return false;
        }

    return true;
}

int main() {
    read();
    printf("%s\n", solve() ? "YES" : "NO");
    return 0;
}