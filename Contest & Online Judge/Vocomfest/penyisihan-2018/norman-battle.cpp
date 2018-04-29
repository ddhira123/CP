#include <bits/stdc++.h>
using namespace std;

int n, m, a, b;
int total_ships[1005], damages[1005], players;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

pair<int, int> scores[1005], grid[1005][1005];

int main() {
  // init
  for (int i = 0; i < 1005; i++) {
    for (int j = 0; j < 1005; j++) {
      grid[i][j] = make_pair(-1, -1);
    }
    scores[i] = make_pair(0, i);
  }

  // read
  scanf("%d %d %d %d", &n, &m, &a, &b);
  players = n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int r, c, l, dir;
      char s[5];

      scanf("%d %d %d %s", &r, &c, &l, s);

      total_ships[i] += l;

      if (s[0] == 'n')
        dir = 0;
      else if (s[0] == 'e')
        dir = 1;
      else if (s[0] == 's')
        dir = 2;
      else if (s[0] == 'w')
        dir = 3;

      // printf("start\n");
      for (int k = 0; k < l; k++) {
        int nr = r + k * dr[dir];
        int nc = c + k * dc[dir];
        // printf("%d %d\n", nr, nc);

        if (grid[nr][nc].first != -1) {
          printf("ERROR_LOCATION_DETECTED\n");
          return 0;
        }
        grid[nr][nc] = make_pair(i, i * m + j);
      }
      // printf("end\n");
    }
  }

  // simulate
  int z, turn = 0;
  scanf("%d", &z);
  for (int i = 0; i < z; i++, turn++, turn %= n) {
    while (total_ships[turn] == 0) {
      turn += 1;
      turn %= n;
    }

    int r, c;
    scanf("%d %d", &r, &c);

    int owner = grid[r][c].first;
    if (owner == -1) {
      continue;
    }

    int ship = grid[r][c].second;

    damages[ship]++;
    int delta = 10 * damages[ship];

    if (--total_ships[owner] == 0) players--;
    if (players == 1) {
      for(int asu = 0 ; asu < n ; asu++) {
        if(total_ships[asu] > 0) {
          scores[asu].first = -1e9;
        }
      }

      break;
    }

    if (owner == turn) {
      scores[turn].first += delta;
    } else {
      scores[turn].first -= delta;
    }

    grid[r][c] = make_pair(-1, -1);
    // printf("turn: %d   owner: %d   delta: %d\n", turn, owner, delta);
  }

  sort(scores, scores + n);

  for (int i = 0; i < n; i++) {
    // printf("%d %d\n", scores[i].second+1, scores[i].first);
    printf("%d\n", scores[i].second + 1);
  }

  return 0;
}