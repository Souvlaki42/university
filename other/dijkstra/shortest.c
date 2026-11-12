#include "shortest.h"
#include <stdio.h>
#include <string.h>

int dijkstra(int cost[N][N], int source, int target) {
  int dist[N], prev[N], selected[N] = {0}, i, m, min, start, d, j;
  char path[N];

  for (i = 1; i < N; i++) {
    dist[i] = INITIAL_DISTANCE;
    prev[i] = -1;
  }

  start = source;
  selected[start] = 1;
  dist[start] = 0;

  while (selected[target] == 0) {
    min = INITIAL_DISTANCE;
    m = 0;
    for (i = 1; i < N; i++) {
      d = dist[start] + cost[start][i];
      if (d < dist[i] && selected[i] == 0) {
        dist[i] = d;
        prev[i] = start;
      }
      if (min > dist[i] && selected[i] == 0) {
        min = dist[i];
        m = i;
      }
    }
    start = m;
    selected[start] = 1;
  }
  start = target;
  j = 0;
  while (start != -1) {
    path[j++] = start + 65;
    start = prev[start];
  }
  path[j] = '\0';

  char *p1, *p2;
  for (p1 = path, p2 = path + strlen(path) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }

  printf("%s\n", path);
  return dist[target];
}