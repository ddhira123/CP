#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 26;
const int MAX_LEN = 3e5 + 5;

string read_string() {
    static char s[MAX_LEN];
    scanf("%s", s);

    return (string)s;
}

struct Node {
    Node *nxt[ALPHA];
    Node *fail;
    int mx;

    Node() {
        fail = NULL;
        for(int i = 0 ; i < ALPHA ; i++) {
            nxt[i] = NULL;
        }
        mx = -1;
    }
};

Node *root = new Node();
int occ[MAX_LEN];
string str;

void add(string s) {
    Node *now = root;

    for(int i = 0 ; i < s.length() ; i++) {
        int ch = s[i] - 'a';

        if(now->nxt[ch] == NULL) {
            now->nxt[ch] = new Node();
        }
        now = now->nxt[ch];
    }

    now->mx = s.length();
}

void make() {
    queue<Node*> q;
    root->mx = 0;

    for(int i = 0 ; i < ALPHA ; i++) {
        if(root->nxt[i] == NULL) {
            root->nxt[i] = root;
        } else {
            root->nxt[i]->fail = root;
            q.push(root->nxt[i]);
        }
    }

    while(!q.empty()) {
        Node *now = q.front();
        q.pop();

        if(now->mx == -1) {
            now->mx = now->fail->mx;
        }

        for(int i = 0 ; i < ALPHA ; i++) {
            if(now->nxt[i] == NULL) {
                now->nxt[i] = now->fail->nxt[i];
            } else {
                now->nxt[i]->fail = now->fail->nxt[i];
                q.push(now->nxt[i]);
            }
        }
    }
}

void init() {
    int n; scanf("%d", &n);
    str = read_string();
    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        string s = read_string();
        add(s);
    }
}

int work(string s) {
    Node *now = root;

    for(int i = 0 ; i < s.length() ; i++) {
        int ch = s[i] - 'a';
        now = now->nxt[ch];

        int cur = i+1;
        int prv = cur - now->mx;

        occ[cur]++;
        occ[prv]--;
    }

    int tot = 0;
    int ret = 0;
    for(int i = s.length() ; i >= 1 ; i--) {
        tot += occ[i];
        if(tot == 0) {
            ret++;
        }
    }

    return ret;
} 

int main() {
    init();
    make();
    printf("%d\n", work(str));
    return 0;
}