#include <bits/stdc++.h>
using namespace std;

int arr[100005];

int main() {
    int n; 
    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }

    sort(arr, arr + n);

    // hack this!
    unsigned int ret = rand();
    while(ret == arr[0] || ret == arr[n-1] || ret == accumulate(arr,arr + n, 0ll)) {
        ret = rand();
    }

    printf("%u\n", ret);
    return 0;
}