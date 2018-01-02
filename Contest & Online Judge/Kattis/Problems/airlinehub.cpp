#include <bits/stdc++.h>
using namespace std;

double PI = acos(-1);

double to_rad(double x) {
    return x / 180 * PI;
}

double dist3d(double lat1, double lon1, double lat2, double lon2){
    lat1 = to_rad(lat1);
    lon1 = to_rad(lon1);

    lat2 = to_rad(lat2);
    lon2 = to_rad(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = pow(sin(dlat/2),2) + cos(lat1) * cos(lat2)* pow(sin(dlon/2),2);

    return (2*atan2(sqrt(a), sqrt(1-a)));
}

double lat[1005], lon[1005];
int n;

bool read() {
    if(scanf("%d", &n) != 1) return false;

    for(int i = 0 ; i < n ; i++) {
        scanf("%lf %lf", &lat[i], &lon[i]);
    }

    return true;
}

void work() {
    double best = 1e9;
    int idx = -1;

    for(int i = 0 ; i < n ; i++) {
        double mx = 0;

        for(int j = 0 ; j < n ; j++) {
            mx = max(mx, dist3d(lat[i], lon[i], lat[j], lon[j]));
        }

        if(mx < best + 1e-9) {
            best = mx;
            idx = i;
        }
    }

    printf("%.2lf %.2lf\n", lat[idx], lon[idx]);
}

int main() {
    while(read()) {
        work();
    }
    return 0;
}