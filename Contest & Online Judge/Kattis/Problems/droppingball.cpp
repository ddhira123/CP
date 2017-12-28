#include <bits/stdc++.h>
using namespace std;

string read_string() {
    static char dummy[100005];
    scanf("%s", dummy);
    return (string)dummy;
}

vector<vector<int>> stree;
vector<string> arr;
int n, m, q;

void read() {
    scanf("%d %d %d", &n, &m, &q);
    arr.push_back("");
    for(int i = 0 ; i < n ; i++) {
        arr.push_back("." + read_string());
    }
}

void build(int id, int l, int r) {
    if(l == r) {
        for(int i = 1 ; i <= m ; i++) {
            if(i == 1) {
                if(arr[l][i] == '/' || arr[l][i+1] == '/') {
                    stree[id][i] = -1;
                } else {
                    stree[id][i] = i+1;
                }
            } else if(i == m) {
                if(arr[l][i] == '\\' || arr[l][i-1] == '\\') {
                    stree[id][i] = -1;
                } else {
                    stree[id][i] = i-1;
                } 
            } else {
                if(arr[l][i] == '/' && arr[l][i-1] == '/') {
                    stree[id][i] = i-1;
                } else if(arr[l][i] == '\\' && arr[l][i+1] == '\\') {
                    stree[id][i] = i+1;
                } else {
                    stree[id][i] = -1;
                }
            }
        }
    } else {
        int chld = id << 1;
        int mid = (l + r) / 2;

        build(chld, l, mid);
        build(chld+1, mid+1, r);

        for(int i = 1 ; i <= m ; i++) {
            if(stree[chld][i] == -1) {
                stree[id][i] = -1;
            } else {
                stree[id][i] = stree[chld+1][stree[chld][i]];
            }
        }
    }
}

void update(int id, int l, int r, int x, int y) {
    if(l == r) {
        arr[x][y] = arr[x][y] == '\\' ? '/' : '\\';
        for(int i = max(1, y-1) ; i <= min(m, y+1) ; i++) {
            if(i == 1) {
                if(arr[l][i] == '/' || arr[l][i+1] == '/') {
                    stree[id][i] = -1;
                } else {
                    stree[id][i] = i+1;
                }
            } else if(i == m) {
                if(arr[l][i] == '\\' || arr[l][i-1] == '\\') {
                    stree[id][i] = -1;
                } else {
                    stree[id][i] = i-1;
                } 
            } else {
                if(arr[l][i] == '/' && arr[l][i-1] == '/') {
                    stree[id][i] = i-1;
                } else if(arr[l][i] == '\\' && arr[l][i+1] == '\\') {
                    stree[id][i] = i+1;
                } else {
                    stree[id][i] = -1;
                }
            }
        }
    } else {
        int chld = id << 1;
        int mid = (l + r) / 2;

        if(x <= mid) {
            update(chld, l, mid, x, y);
        } else {
            update(chld+1, mid+1, r, x, y);
        }

        for(int i = 1 ; i <= m ; i++) {
            if(stree[chld][i] == -1) {
                stree[id][i] = -1;
            } else {
                stree[id][i] = stree[chld+1][stree[chld][i]];
            }
        }
    }
}

void work() {
    if(m == 1) {
        for(int i = 0 ; i < q ; i++) {
            int opt;
            scanf("%d", &opt);

            if(opt == 1) {
                int x, y;
                scanf("%d %d", &x, &y);
            } else {
                int x; scanf("%d", &x);
                printf("-1\n");
            }
        }
    }
    else if(m < 350) {
        stree = vector<vector<int>>(4 * n, vector<int>(m+1, 0));
        build(1, 1, n);

        for(int i = 0 ; i < q ; i++) {
            int opt;
            scanf("%d", &opt);

            if(opt == 1) {
                int x, y;
                scanf("%d %d", &x, &y);
                update(1, 1, n, x, y);
            } else {
                int x; scanf("%d", &x);
                printf("%d\n", stree[1][x]);
            }
        }
    } else {
        for(int i = 0 ; i < q ; i++) {
            int opt;
            scanf("%d", &opt);

            if(opt == 1) {
                int x, y;
                scanf("%d %d", &x, &y);
                arr[x][y] = arr[x][y] == '\\' ? '/' : '\\';
            } else {
                int x; scanf("%d", &x);
                
                for(int row = 1 ; row <= n ; row++) {
                    if(x == 1) {
                        if(arr[row][x] == '/' || arr[row][x+1] == '/') {
                            x = -1;
                            break;
                        } else {
                            x++;
                        }  
                    } else if(x == m) {
                        if(arr[row][x] == '\\' || arr[row][x-1] == '\\') {
                            x = -1;
                            break;
                        } else {
                            x--;
                        }
                    } else {
                        if(arr[row][x] == '\\' && arr[row][x+1] == '\\') {
                            x++;
                        } else if(arr[row][x] == '/' && arr[row][x-1] == '/') {
                            x--;
                        } else {
                            x = -1;
                            break;
                        }
                    }
                }

                printf("%d\n", x);
            }
        }
    }
}

int main() {
    read();
    work();
    return 0;
}