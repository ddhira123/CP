#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int arr[N];
int n;

int main() {
  cin >> n;
  for (int i = 0 ; i < n ; i++)
    cin >> arr[i];
  
  int sum = 0;
  int k = 0;
  for (int i = 0 ; i < n ; i++) {
    sum += arr[i];
    k = max(k, arr[i]);
  }
  
  // int k = 0;
  while (k * n <= 2 * sum) k++;

  cout << k << endl;
  return 0;
}