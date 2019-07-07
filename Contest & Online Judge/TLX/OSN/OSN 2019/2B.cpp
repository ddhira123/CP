#include <bits/stdc++.h>
using namespace std;

int R, C, Q;
pair<int, int> A, B;

int myAsk(pair<int, int> x) {
  int ret = abs(A.first - x.first) + abs(A.second - x.second);
  ret = min(ret, abs(B.first - x.first) + abs(B.second - x.second));
  return ret;
}

int ask(pair<int, int> x) {
  // return myAsk(x);
  printf("? %d %d\n", x.first, x.second);
  fflush(stdout);

  int ret; scanf("%d", &ret);
  return ret;
}

vector<pair<int, int>> solve() {
  vector<pair<int, int>> interest = {{1, 1}, {1, C}, {R, C}, {R, 1}};
  vector<int> d;

  for (auto it : interest) {
    d.push_back(ask(it));
  }

  // printf("A = {%d, %d}, B = {%d, %d}\n", A.first, A.second, B.first,
  // B.second); for (int x : d) printf("%d ", x); puts("");

  // x-1 + y-1 + R-x + y-1 = d[0] + d[3]
  // R + 2y - 3 = d[0] + d[3]
  // y = (d[0] + d[3] - R + 3) / 2
  if ((d[0] + d[3] - R + 3) % 2 == 0) {
    int y = (d[0] + d[3] - R + 3) / 2;
    int x = d[0] + 2 - y;

    if (1 <= x && x <= R && 1 <= y && y <= C && ask({x, y}) == 0) {
      // x-1 + C-y + R-x + C-y = d[1] + d[2]
      // R + 2C - 2y -1 = d[1] + d[2]
      // y = -(d[1] + d[2] + 1 - 2C - R) / 2
      int temp = d[1] + d[2] + 1 - 2 * C - R;
      if (temp % 2 == 0) {
        int y2 = -temp / 2;
        int x2 = d[1] - C + y2 + 1;

        if (1 <= x2 && x2 <= R && 1 <= y2 && y2 <= C) {
          return {{x, y}, {x2, y2}};
        }
      }
    }
  }

  // x-1 + y-1 + x-1 + C-y = d[0] + d[1]
  // C + 2x - 3 = d[0] + d[1]
  // x = (d[0] + d[1] - C + 3) / 2
  if ((d[0] + d[1] - C + 3) % 2 == 0) {
    int x = (d[0] + d[1] - C + 3) / 2;
    int y = d[0] + 2 - x;
    // printf("x %d y %d\n", x, y);

    if (1 <= x && x <= R && 1 <= y && y <= C) {
      // R-x + C-y + R-x + y-1 = d[2] + d[3]
      // 2R + C - 2x -1 = d[2] + d[3]
      // x = -(d[2] + d[3] + 1 - 2R - C) / 2
      int temp = d[2] + d[3] + 1 - 2 * R - C;
      if (temp % 2 == 0) {
        int x2 = -temp / 2;
        int y2 = R - x2 + C - d[2];
        // printf("x2 %d y2 %d\n", x2, y2);
        if (1 <= x2 && x2 <= R && 1 <= y2 && y2 <= C) {
          return {{x, y}, {x2, y2}};
        }
      }
    }
  }

  return {{-1, -1}, {-1, -1}};
}

int main() {
  // stress test
  // srand(time(NULL));
  // R = rand() % 100 + 1;
  // C = rand() % 100 + 1;
  // // R = 9, C = 3;

  // printf("R = %d, C = %d\n", R, C);

  // for (int i = 1; i <= R; i++)
  //   for (int j = 1; j <= C; j++)
  //     for (int ii = 1; ii <= R; ii++)
  //       for (int jj = 1; jj <= C; jj++) {
  //         A = {i, j};
  //         B = {ii, jj};
  //         vector<pair<int, int>> ret = solve();

  //         if ((ret[0] == A && ret[1] == B) || (ret[0] == B && ret[1] == A)) {
  //         } else {
  //           printf(
  //               "WA -- expected (%d,%d) and (%d,%d), got (%d,%d) and (%d,%d)\n",
  //               A.first, A.second, B.first, B.second, ret[0].first,
  //               ret[0].second, ret[1].first, ret[1].second);
  //           return 0;
  //         }
  //       }

  scanf("%d %d %d", &R, &C, &Q);
  vector<pair<int, int>> ret = solve();

  printf("! %d %d %d %d\n", ret[0].first, ret[0].second, ret[1].first, ret[1].second);
  fflush(stdout);
  return 0;
}
