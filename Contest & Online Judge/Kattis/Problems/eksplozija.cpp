#include <bits/stdc++.h>
using namespace std;

char s[1000005];
char t[40];

char ans[1000005]; 
int ans_len;

void read() {
    scanf("%s%s", s, t);
}

void work() {
    int s_len = strlen(s);
    int t_len = strlen(t);

    for(int i = 0 ; i < s_len ; i++) {
        ans[ans_len++] = s[i];

        if(ans_len >= t_len) {
            bool ok = true;

            for(int i = 0 ; i < t_len ; i++) {
                if(ans[ans_len - t_len + i] != t[i]) {
                    ok = false;
                    break;
                }
            }

            if(ok) {
                ans_len -= t_len;
            }
        }
    }

    if(ans_len == 0) {
        printf("FRULA\n");
        return;
    }

    ans[ans_len] = '\0';
    printf("%s\n", ans);
}

int main() {
    read();
    work();
    return 0;
}