#include<bits/stdc++.h>
using namespace std;

char str[10];
int n, a[20000001];
int dict[15];

string nada[] = {"Do", "Do#", "Re", "Re#", "Mi", "Fa",
                "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
unordered_map<string, int> nadaPos;

void insertEntry(int s, int mask){
    dict[s] = mask;
}

int cuts[20000001];

int main(){
    //TODO: Insert 12 tangga nada
    for(int i = 0; i < 12; i++){
        int tmpVal = 0;
        tmpVal += (1<<((0+i)%12));
        tmpVal += (1<<((1+i)%12));
        tmpVal += (1<<((3+i)%12));
        tmpVal += (1<<((5+i)%12));
        tmpVal += (1<<((7+i)%12));
        tmpVal += (1<<((8+i)%12));
        tmpVal += (1<<((10+i)%12));
        dict[i] = tmpVal;
        nadaPos[nada[i]] = i;
    }
    //110101011010 0
    //011010101101 1
    //101101010110 2
    //010110101011 3
    //101011010101 4
    //110101101010 5
    //011010110101 6
    //101101010110 7 
    //010110101011 8
    //101011010101 9
    //110101101010 10
    //011010110101 11
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++){
        int asd = 0;
        str[asd] = getchar();
        while (str[asd] != '\n') {
            asd++;
            str[asd] = getchar();
        }
        str[asd] = '\0';
        string s = (string)str;

        int j = -1;
        if (str[0] == 'D') {
            j = 0 + (str[2] == '#');
        } else if (str[0] == 'R') {
            j = 2 + (str[2] == '#');
        } else if (str[0] == 'M') {
            j = 4;
        } else if (str[0] == 'F') {
            j = 5 + (str[2] == '#');
        } else if (str[0] == 'S' && str[1] == 'o') {
            j = 7 + (str[3] == '#');
        } else if (str[0] == 'L') {
            j = 9 + (str[2] == '#');
        } else {
            j = 11;
        }
        
        a[i] = dict[j];
        a[i + n] = a[i];
        // for(int j = 0; j <= 12; j++){
        //     if(strcmp(str, nada[j].c_str()) == 0){
        //         a[i] = dict[j];
        //         a[i+n] = a[i];
        //         break;
        //     }
        // }
    }
    //for(int i = 0; i < 2*n; i++) printf("[%d]", a[i]); printf("\n");

    int cutlen = 0;
    cuts[cutlen++] = 0;
    // vector<int> cuts;
    // cuts.push_back(0);
    int ans = 20000000;
    int idx = 0, lidx = 0, curMask = a[0];
    while(idx < 2*n){
        while(idx < 2*n && (curMask&a[idx]) > 0){
            curMask &= a[idx];
            idx++;
        }
        //printf("Start again at %d\n", idx);
        while(lidx+1 < cutlen && cuts[lidx+1]+n <= idx) ++lidx;
        if(cuts[lidx]+n <= idx){
            ans = min(ans, (int)cutlen-lidx);
            //printf("(%d)\n", (int)cuts.size()-lidx);
        }
        cuts[cutlen++] = idx;
        // cuts.push_back(idx);
        curMask = a[idx];
    }
    //printf("===\n");
    // cuts.clear();
    // cuts.push_back(2*n - 1);
    // idx = 2*n-1, lidx = 0, curMask = a[2*n-1];
    // while(idx >= 0){
    //     while(idx >= 0 && (curMask&a[idx]) > 0){
    //         curMask &= a[idx--];
    //     }
    //     //printf("Start again at %d\n", idx);
    //     while(lidx+1 < cuts.size() && idx+n <= cuts[lidx+1]) ++lidx;
    //     if(idx+n <= cuts[lidx]){
    //         ans = min(ans, (int)cuts.size()-lidx);
    //         //printf("(%d)\n", (int)cuts.size()-idx);
    //     }
    //     cuts.push_back(idx);
    //     curMask = a[idx];
    // }
    printf("%d\n", ans);
}